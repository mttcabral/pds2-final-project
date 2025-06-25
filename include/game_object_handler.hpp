#ifndef HANDLER_H
#define HANDLER_H

#include <list>
#include <memory>
#include <allegro5/allegro.h>
#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"

enum Ambient {NONE, FLAPPY, EELS};

class Handler {
private:
    bool playing = false;
    Player guy;
    std::list<std::unique_ptr<Pipe>> obstacles;
    int time = 0;
    Ambient dynamic = NONE;
    float gameSpeed = 1;
public:
    int gameOn(ALLEGRO_TIMER& timer, ALLEGRO_TIMER& animation_timer, ALLEGRO_EVENT_QUEUE& eventQueue, const int SCREEN_H, const int SCREEN_W);
    void addObstacle(ALLEGRO_BITMAP * image, Spritesheet * eelImage);
    void drawAll();
    bool checkCollisions();
    bool outOfBorders();
    void drawObstacles();
    void death();
    int sortBetween(int x, int y);

    void updateAmbient();
};

#endif
