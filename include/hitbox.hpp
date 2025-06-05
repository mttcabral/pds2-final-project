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
        Hitbox(float pX, float pY, hitboxType t = hitboxType::Negative); 

        void invertType();
        bool updatePosition() override;
        
        void setTarget(Drawable *target);

        virtual bool checkColision() = 0;

        virtual ~Hitbox();
};
    
class RectangleHitbox: public Hitbox {
    private:
        float width, height;
        Point vertex[2];
    public: 
        RectangleHitbox(float pX, float pY, float w, float h, hitboxType t = hitboxType::Negative);
        
        bool checkColision() override;
        
        float getWidth();
        float getHeight();
        Point getVertex0();
        Point getVertex1();
        

        //rotateHitbox();
};

class CircleHitbox: public Hitbox {
    private:
        float radius;
    public:
        CircleHitbox(float pX, float pY, float r, hitboxType t = hitboxType::Negative);
};











#endif