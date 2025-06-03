#ifndef ACTIVE_H
#define ACTIVE_H

#include "game_object.hpp"
#include "hitbox.hpp"



class ActiveObject: public Drawable {
    protected:
        Hitbox * hb;
};

class basicPlayer: public ActiveObject {
    private:
        double xAxis = 200;
        double lengthSize = 100;
    public:
        basicPlayer();

        void updatePosition();
        void updateVelocity();

        ~basicPlayer();
};











#endif