#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.hpp"
#include "hitbox.hpp"



class Entity: public Drawable {
    protected:
        Hitbox * hb;
    public: 
        Entity(double x, double y, double sX, double sY);
        Entity(double x, double y);
};

class BasicPlayer: public Entity {
    private:
        double xAxis = 200;
        double lengthSize = 100;
    public:
        BasicPlayer();

        void updatePosition();
        void updateVelocity();

        ~BasicPlayer();
};











#endif