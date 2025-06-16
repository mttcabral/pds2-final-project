#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "polygon.hpp"

//Game Object Superclass
class GameObject {
    private:
        //Vector for position of object on the screen
        Point pos;
        
    protected:
        GameObject(const Point& position);
        GameObject(float pX, float pY);

        void setPosX(float x);
        void setPosY(float y);
        void setPos(const Point&p);
        
    public:
        Point getPos();
        float getPosX();
        float getPosY();

        virtual bool updatePosition() = 0;
        
};

//Father class for all classes that are drawn on display and possibly move around
class Drawable : public GameObject {
    private:
        //Vector for object speed
        Point speed;
    protected:
        Drawable(const Point &pos, const Point &spd);
        Drawable(const Point &pos);

        void setSpeedX(float x);
        void setSpeedY(float y);
        void setSpeed(const Point &pos);

    public:
        virtual void draw() = 0;
        virtual void updateSpeed() = 0;

        void addSpeedVector(const Point &spd);
        void addSpeedX(float x);
        void addSpeedY(float y);

        Point getSpeed();
        float getSpeedX();
        float getSpeedY();
};















#endif