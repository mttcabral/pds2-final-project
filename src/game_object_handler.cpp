#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"
#include "game_object_handler.hpp"
#include "cooldown.hpp"
#include "animation.hpp"
#include "passive.hpp"
#include <iostream>
#include <string>
#include <random>
#include <chrono>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

int Handler::gameOn(ALLEGRO_TIMER &timer, ALLEGRO_TIMER &animation_timer, ALLEGRO_EVENT_QUEUE &eventQueue, const int SCREEN_H, const int SCREEN_W)
{

    BackgroundHandler bgLayer3("assets/bg/sea.png",900,600,-1,SCREEN_W, SCREEN_H);
    BackgroundHandler bgLayer2("assets/bg/clouds.png",900,600,-4,SCREEN_W, SCREEN_H);
    BackgroundHandler bgLayer1("assets/bg/rocks.png",2700,600,-10,SCREEN_W, SCREEN_H);
    ALLEGRO_FONT* scoreCount = al_load_font("assets/PressStart2P-Regular.ttf", 30, 0);
    
    ALLEGRO_COLOR baseBackgroundColor = al_map_rgba_f(0.7,0.7,0.9,1);
    al_start_timer(&timer);
    bool redraw = false;
    playing = true;
    time = 0;
    Cooldown jumpCD(0);
    Cooldown obstacleCD(4);
    obstacleCD.restartCooldown();

    ALLEGRO_BITMAP * pipeSprite = al_load_bitmap("assets/long.png");

    while (playing)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(&eventQueue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (!playing) break;
            time++;
            if (event.timer.source == &timer) {
                guy.updateSpeed();
                guy.updatePosition();
                guy.updatePlayerState();               
                bgLayer3.updateBackgroundPosition();
                bgLayer2.updateBackgroundPosition();
                bgLayer1.updateBackgroundPosition();
            } else if (event.timer.source == &animation_timer) {
                guy.updateAnimation();
            }
            if (obstacleCD.isCooldownUp())
            {
                addObstacle(pipeSprite);
                obstacleCD.setRechargeTime(sortBetween(2, 3));
                obstacleCD.restartCooldown();
            }
            for (auto it = obstacles.begin(); it != obstacles.end(); /* não incremente aqui */) {
                (*it)->updateSpeed();
                (*it)->updatePosition();
                if ((*it)->getPosX() < -200) {
                    it = obstacles.erase(it);
                } else {
                ++it;
                }
            }
            if(checkCollisions() || outOfBorders()) return -1;
            redraw = true;
            jumpCD.updateCooldown();
            obstacleCD.updateCooldown();
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_SPACE:
            case ALLEGRO_KEY_UP:
                if (jumpCD.isCooldownUp())
                {
                    guy.jump();
                    jumpCD.restartCooldown();
                    //sheetTest.resetAnimation();
                }
                break;
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            playing = false;
            break;
        }
        if (redraw && al_is_event_queue_empty(&eventQueue))
        {
            // refresh display
            al_clear_to_color(baseBackgroundColor);    
            string scoreText = to_string(time);
            //bg
            bgLayer3.drawBackground();
            bgLayer2.drawBackground();
            bgLayer1.drawBackground();
            // objects
            drawAll();
            // score at playing state
            al_draw_text(scoreCount, al_map_rgb(255,255,255), (SCREEN_W/2), 30, ALLEGRO_ALIGN_CENTER, scoreText.c_str());
            al_flip_display(); // updates the display with the new frame
            redraw = false;
        }
    }
    
    al_destroy_bitmap(pipeSprite);

    return time;
}
void Handler::addObstacle(ALLEGRO_BITMAP * image)
{
    int x = sortBetween(0, 300);
    if(x>50){
        obstacles.push_back(unique_ptr<Pipe>(new Pipe(Point(1000, 800-x), 50, 300, image)));
        obstacles.push_back(unique_ptr<Pipe>(new Pipe(Point(1000, 300-x), 50, 300, image)));        
    }else{
        obstacles.push_back(unique_ptr<Pipe>(new Pipe(Point(1000, 425-x), 50, 300, image)));       
    }


}
bool Handler::outOfBorders(){
    if(guy.getPosY() > 600 || guy.getPosY() < 0){
        death();
        return true;
    }
    return false;
}
bool Handler::checkCollisions()
{
    for (auto& obj : obstacles)
    {
        if (isColidingSAT(guy.getHitbox()->getPolygon(),
                        obj->getHitbox()->getPolygon()))
        {
            death();
            return true;
        }
    }
    return false;
}
void Handler::drawAll()
{
    guy.draw();
    for (auto& obj : obstacles)
    {
        obj->draw();
    }
}
void Handler::death()
{
    obstacles.clear();
    playing = false;
}
int Handler::sortBetween(int min, int max) {
    static std::mt19937 motor(std::random_device{}());
    std::uniform_int_distribution<int> distribuicao(min, max);
    return distribuicao(motor);
}