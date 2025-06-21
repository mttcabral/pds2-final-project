#ifndef HANDLER_H
#define HANDLER_H

#include <list>
#include <memory>
#include <allegro5/allegro.h>
#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"

class Handler {
private:
    bool playing = false;
    std::unique_ptr<Player> guy;
    std::list<std::unique_ptr<Pipe>> obstacles;
    int time = 0;
public:
    int gameOn(ALLEGRO_TIMER& timer, ALLEGRO_EVENT_QUEUE& eventQueue);
    void addObstacle();
    void drawAll();
    bool checkCollisions();
    void drawObstacles();
    void death();
    int sortBetween(int x, int y);
};

#endif
