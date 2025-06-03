#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.hpp"
#include "hitbox.hpp"

const double BASE_GRAVITY = 10;
const double BASE_X_MOVEMENT = 20;

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

        bool updatePosition() override;
        void updateVelocity() override;

        void jump();
        
        ~BasicPlayer();
};











#endif