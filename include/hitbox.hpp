#ifndef HITBOX_H
#define HITBOX_H

#include "game_object.hpp"

enum class hitboxType {
    Positive,
    Negative
};

class Hitbox: public GameObject{
    private:
        hitboxType type;
    public: 
        Hitbox(double pX, double pY, hitboxType t = hitboxType::Negative); 

        void invertType();
        void updatePosition(double pX, double pY);

        virtual bool checkColision() = 0;
};

class RectangleHitbox: public Hitbox {};

class CircleHitbox: public Hitbox {};











#endif