#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"
#include "initializer_allegro.hpp"
#include "game_object_handler.hpp"
#include "cooldown.hpp"
#include "animation.hpp"
#include "passive.hpp"
#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

// Game constants:
// const float FPS = 30;                                      // Frames per second (in cooldown.hpp)
// const float ANIM_FPS = 12;                                 // Frames per second for animation
const int SCREEN_W = 800;                                     // Screen width in pixels
const int SCREEN_H = 600;                                     // Screen height in pixels
const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);   // Background color (black)

int main(){

    // Basic Allegro pointers:
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *eventQueue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    ALLEGRO_TIMER *animation_timer = nullptr;
    
    // Initializations:

    //V-Sync:
    //tries to solve frame-skipping bug, still not solved !!!
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

    if(!initialize_allegro()) return 1;

    if(!initialize_event_queue(eventQueue)) return 1;

    if(!initialize_display(display,SCREEN_W,SCREEN_H)) return 1;

    if(!initialize_timer(timer,FPS)) return 1;
    if(!initialize_timer(animation_timer,ANIM_FPS)) return 1;

    // Register event sources for the event queue
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_timer_event_source(animation_timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    // Start the timer to control game speed
    al_start_timer(timer);
    al_start_timer(animation_timer);

    // Game is being played control
    bool gameActive = true;
    
    //Redraw condition, so that the game is rendered separately from other events in queue
    bool redraw = false;

    ALLEGRO_COLOR colisionIndicatorColor = al_map_rgb(20,140,20);

    // Basic player object for testing
    //BasicPlayer squareguy;
    Player guy;
    //guy.loadSprite("assets/guy.png");
    // Basic obstacle object for testing
    Pipe obstacle(Point(800,300),50,300);
    //Pipe obstacle(Point(200,600),128,128);
    obstacle.loadSprite("assets/long.png");

    ALLEGRO_COLOR baseBackgroundColor = al_map_rgba_f(0.7,0.7,0.9,1);
    
    //testing sub bitmaps
    //TriggerSpritesheet sheetTest("assets/kirby.png",8,26,0);
    
    //testing background
    //the timing is not perfet at all, fix this later
    BackgroundHandler bgLayer3("assets/bg/sea.png",900,600,-1,SCREEN_W, SCREEN_H);
    BackgroundHandler bgLayer2("assets/bg/clouds.png",900,600,-4,SCREEN_W, SCREEN_H);
    BackgroundHandler bgLayer1("assets/bg/rocks.png",2700,600,-10,SCREEN_W, SCREEN_H);

    //testing cooldown
    Cooldown jumpCD(0);

    while (gameActive) {
        
        ALLEGRO_EVENT event;

        al_wait_for_event(eventQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
            if (event.timer.source == timer) {
                guy.updateSpeed();
                guy.updatePosition(); 
                guy.updatePlayerState();
                obstacle.updateSpeed();
                obstacle.updatePosition();
                
                bgLayer3.updateBackgroundPosition();
                bgLayer2.updateBackgroundPosition();
                bgLayer1.updateBackgroundPosition();


                obstacle.getHitbox()->rotateHitbox(PI/180);

                if (isColidingSAT(guy.getHitbox()->getPolygon(),
                                obstacle.getHitbox()->getPolygon())){
                    colisionIndicatorColor = al_map_rgb(140,20,20);
                }else {
                    colisionIndicatorColor = al_map_rgb(20,140,20);
                } //placeholder colision detection and visualization
                
                redraw = true;
                
                jumpCD.updateCooldown();
                //cout << jumpCD.getCurrentPorcentage() << '\n';
                
            } else if (event.timer.source == animation_timer) {
                guy.updateAnimation();
            }

            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_SPACE: case ALLEGRO_KEY_UP:
                        if (jumpCD.isCooldownUp()) {
                            guy.jump();
                            jumpCD.restartCooldown();
                            //sheetTest.resetAnimation();
                        }
                        //cout << "Jump\n";
                        break;
                    }
            break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                gameActive = false;
            break;
        }

        //redraw frame
        if (redraw && al_is_event_queue_empty(eventQueue)) {
            //refresh display
            al_clear_to_color(baseBackgroundColor);

            //bg
            bgLayer3.drawBackground();
            bgLayer2.drawBackground();
            bgLayer1.drawBackground();

            //objects
            guy.draw();
            obstacle.draw();

            //colision
            //al_draw_filled_circle(800,400,30,colisionIndicatorColor); 
            

            /*
            al_draw_scaled_rotated_bitmap(
            sheetTest.getCurrentFrame(),
            al_get_bitmap_width(sheetTest.getCurrentFrame())/2,
            al_get_bitmap_height(sheetTest.getCurrentFrame())/2,
            guy.getPosX(),guy.getPosY(),
            2.5,2.5, 
            0,0);
            */

            al_flip_display(); //updates the display with the new frame 

            redraw = false;
        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    al_destroy_timer(timer);
    al_destroy_timer(animation_timer);
    



    return 0;
}