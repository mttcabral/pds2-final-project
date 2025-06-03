#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

struct Point{
    double x,y;

    Point(double x, double y): x(x), y(y) {}
    Point(): x(0), y(0) {}
};

class GameObject {
    private:
        Point pos;
        
    protected:
        GameObject(double pX, double pY);

        void setPosX(double x);
        void setPosY(double y);
        
    public:
        Point getPos();
        double getPosX();
        double getPosY();

        virtual bool updatePosition() = 0;
        
};


class Drawable : public GameObject {
    private:
        double speedX, speedY;
    protected:
        Drawable(double x, double y, double sX, double sY);
        Drawable(double x, double y);

        void setSpeedX(double x);
        void setSpeedY(double y);

    public:
        virtual void draw() = 0;
        virtual void updateSpeed() = 0;

        void addSpeedX(double x);
        void addSpeedY(double y);

        double getSpeedX();
        double getSpeedY();
};















#endif