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
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/**
 * @brief Executa o loop principal do jogo.
 *
 * @param timer Timer principal do jogo.
 * @param animation_timer Timer para animações.
 * @param eventQueue Fila de eventos do Allegro.
 * @param SCREEN_H Altura da tela.
 * @param SCREEN_W Largura da tela.
 * @return int Pontuação final (tempo de sobrevivência).
 */
int Handler::gameOn(ALLEGRO_TIMER &timer, ALLEGRO_TIMER &animation_timer, ALLEGRO_EVENT_QUEUE &eventQueue, const int SCREEN_H, const int SCREEN_W)
{

    this->dynamic = NONE;

    BackgroundHandler bgLayer3("assets/bg/sea.png", 900, 600, -1, SCREEN_W, SCREEN_H);
    BackgroundHandler bgLayer2("assets/bg/clouds.png", 900, 600, -4, SCREEN_W, SCREEN_H);
    BackgroundHandler bgLayer1("assets/bg/rocks.png", 2700, 600, -10, SCREEN_W, SCREEN_H);
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(10);
    ALLEGRO_SAMPLE *jumping_soundeffect = al_load_sample("assets/music/soundeffect/jumping_soundeffect.wav");
    ALLEGRO_FONT *scoreCount = al_load_font("assets/PressStart2P-Regular.ttf", 30, 0);

    ALLEGRO_COLOR baseBackgroundColor = al_map_rgba_f(0.7, 0.7, 0.9, 1);
    al_start_timer(&timer);
    bool redraw = false;
    playing = true;
    time = 0;
    Cooldown jumpCD(0);
    Cooldown obstacleCD(4);
    obstacleCD.restartCooldown();

    ALLEGRO_BITMAP *pipeSprite = al_load_bitmap("assets/obstacle/sandPipe.png");

    Spritesheet eelSprite("assets/obstacle/eel.png", 24, 366, 0);

    this->gameSpeed = 1;
    Pipe::updateScreenSpeed(-7);

    while (playing)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(&eventQueue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (!playing)
                break;

            if (event.timer.source == &timer)
            {
                time++;
                if (this->gameSpeed >= 1)
                    this->time = this->time + this->gameSpeed;
                else
                    time++;

                this->updateAmbient();

                guy.updateSpeed();
                guy.updatePosition();
                guy.updatePlayerState();
                bgLayer3.updateBackgroundPosition();
                bgLayer2.updateBackgroundPosition();
                bgLayer1.updateBackgroundPosition();
            }
            else if (event.timer.source == &animation_timer)
            {
                guy.updateAnimation();
                eelSprite.advanceFrame();
            }
            if (obstacleCD.isCooldownUp())
            {
                addObstacle(pipeSprite, &eelSprite);
                obstacleCD.setRechargeTime(sortBetween(2, 3));
                obstacleCD.restartCooldown();
            }
            for (auto it = obstacles.begin(); it != obstacles.end(); /* não incremente aqui */)
            {
                (*it)->updateSpeed();
                (*it)->updatePosition();
                if ((*it)->getPosX() < -200)
                {
                    it = obstacles.erase(it);
                }
                else
                {
                    ++it;
                }
            }
            if (checkCollisions() || outOfBorders())
                return time;

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
                    al_play_sample(jumping_soundeffect, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                    jumpCD.restartCooldown();
                    // sheetTest.resetAnimation();
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
            // bg
            bgLayer3.drawBackground();
            bgLayer2.drawBackground();
            bgLayer1.drawBackground();
            // objects
            drawAll();
            // score at playing state
            al_draw_text(scoreCount, al_map_rgb(255, 255, 255), (SCREEN_W / 2), 30, ALLEGRO_ALIGN_CENTER, scoreText.c_str());
            al_flip_display(); // updates the display with the new frame
            redraw = false;
        }
    }

    al_destroy_bitmap(pipeSprite);

    return time;
}

/**
 * @brief Adiciona um novo obstáculo ao jogo.
 *
 * @param image Bitmap do obstáculo tipo Pipe.
 * @param eelImage Spritesheet do obstáculo tipo Eel.
 */
void Handler::addObstacle(ALLEGRO_BITMAP *image, Spritesheet *eelImage)
{
    int x = sortBetween(80, 430);
    switch (this->dynamic)
    {
    case NONE:
        break;
    case FLAPPY:
        obstacles.push_back(unique_ptr<Pipe>(new Pipe(Point(1000, 910 - x), 145, 470, image)));
        obstacles.push_back(unique_ptr<Pipe>(new Pipe(Point(1000, 190 - x), 145, 470, image, true)));
        break;
    case EELS:
        obstacles.push_back(unique_ptr<Pipe>(new Eel(Point(1000, 50 + x), eelImage)));
        break;
    }
}

/**
 * @brief Verifica se o jogador saiu dos limites da tela.
 *
 * @return true Se saiu dos limites.
 * @return false Caso contrário.
 */
bool Handler::outOfBorders()
{
    if (guy.getPosY() > 600 || guy.getPosY() < 0)
    {
        death();
        return true;
    }
    return false;
}

/**
 * @brief Verifica colisões entre o jogador e os obstáculos.
 *
 * @return true Se houve colisão.
 * @return false Caso contrário.
 */
bool Handler::checkCollisions()
{
    for (auto &obj : obstacles)
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

/**
 * @brief Desenha todos os objetos do jogo na tela.
 */
void Handler::drawAll()
{
    guy.draw();
    for (auto &obj : obstacles)
    {
        obj->draw();
    }
}

/**
 * @brief Executa procedimentos de morte do jogador.
 */
void Handler::death()
{
    obstacles.clear();
    playing = false;
}

/**
 * @brief Sorteia um número inteiro entre min e max.
 *
 * @param min Valor mínimo.
 * @param max Valor máximo.
 * @return int Número sorteado.
 */
int Handler::sortBetween(int min, int max)
{
    static std::mt19937 motor(std::random_device{}());
    std::uniform_int_distribution<int> distribuicao(min, max);
    return distribuicao(motor);
}

/**
 * @brief Atualiza o ambiente do jogo, mudando dinâmicas e velocidade.
 */
void Handler::updateAmbient()
{
    int mark = this->time / 200;

    if (this->time > 600 && this->gameSpeed < 1.3)
    {
        this->gameSpeed = 1.3;
        Pipe::updateScreenSpeed(-7 * this->gameSpeed);
    }
    else if (this->time > 1200 && this->gameSpeed < 1.8)
    {
        this->gameSpeed = 1.8;
        Pipe::updateScreenSpeed(-7 * this->gameSpeed);
    }
    switch (this->dynamic)
    {
    case NONE:
        // cout << "none" << '\n';
        if (this->time >= 50)
            this->dynamic = FLAPPY;
        break;
    case FLAPPY:
        // cout << "flappy" << '\n';
        if (mark % 3 == 0 && this->time > 200)
            this->dynamic = EELS;

        break;
    case EELS:
        // cout << "eel" << '\n';
        if (mark % 3 != 0)
            this->dynamic = FLAPPY;

        break;
    }
}