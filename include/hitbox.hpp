#ifndef HITBOX_H
#define HITBOX_H

#include "game_object.hpp"

enum class hitboxType {
    Positive,
    Negative
}; //maybe overload the operator'!' to invert values (?)

class Hitbox: public GameObject{
    private:
        hitboxType type;
        Drawable* target;
    public: 
        Hitbox(double pX, double pY, hitboxType t = hitboxType::Negative); 

        void invertType();
        bool updatePosition() override;
        
        void setTarget(Drawable *target);

        virtual bool checkColision() = 0;

        virtual ~Hitbox();
};
    
class RectangleHitbox: public Hitbox {
    private:
        double width, height;
        Point vertex[2];
    public: 
        RectangleHitbox(double pX, double pY, double w, double h, hitboxType t = hitboxType::Negative);
        
        bool checkColision() override;
        
        double getWidth();
        double getHeight();
        Point getVertex0();
        Point getVertex1();
        

        //rotateHitbox();
};

class CircleHitbox: public Hitbox {
    private:
        double radius;
    public:
        CircleHitbox(double pX, double pY, double r, hitboxType t = hitboxType::Negative);
};











#endif