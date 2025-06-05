#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "polygon.hpp"


class GameObject {
    private:
        Point pos;
        
    protected:
        GameObject(const Point& position);
        GameObject(float pX, float pY);

        void setPosX(float x);
        void setPosY(float y);
        
    public:
        Point getPos();
        float getPosX();
        float getPosY();

        virtual bool updatePosition() = 0;
        
};


class Drawable : public GameObject {
    private:
        float speedX, speedY;
    protected:
        Drawable(float x, float y, float sX, float sY);
        Drawable(float x, float y);

        void setSpeedX(float x);
        void setSpeedY(float y);

    public:
        virtual void draw() = 0;
        virtual void updateSpeed() = 0;

        void addSpeedX(float x);
        void addSpeedY(float y);

        float getSpeedX();
        float getSpeedY();
};















#endif