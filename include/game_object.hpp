#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class GameObject {
    private:
        double posX, posY;
        double speedX, speedY;
    protected:
        GameObject(double pX, double pY, double sX, double sY);
        GameObject(double pX, double pY);

        void setPosX(double x);
        void setPosY(double y);
        void setSpeedX(double x);
        void setSpeedY(double y);
    public:
        void addSpeedX(double x);
        void addSpeedY(double y);

        double getPosX();
        double getPosY();
        double getSpeedX();
        double getSpeedY();

        virtual void updatePosition() = 0;
        virtual void updateVelocity() = 0;
};


class Drawable : public GameObject {
    public:
        virtual void draw() = 0;
};















#endif