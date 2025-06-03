#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.hpp"
#include "hitbox.hpp"

const double BASE_GRAVITY = 10;
const double BASE_X_MOVEMENT = 20;
const double X_AXIS = 200;

class Entity: public Drawable {
    protected:
        Hitbox * hb;
    public: 
        Entity(double x, double y, double sX, double sY);
        Entity(double x, double y);

        Hitbox *getHitbox();
};

class BasicPlayer: public Entity {
    private:
        double xAxis = X_AXIS;
        double lengthSize = 100;
    public:
        BasicPlayer();

        RectangleHitbox *getHitboxAABB();

        bool updatePosition() override;
        void updateSpeed() override;

        void jump();

        void draw() override;
        
        ~BasicPlayer();
};











#endif