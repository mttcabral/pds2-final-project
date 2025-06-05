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
        Hitbox(const Point& center, hitboxType t = hitboxType::Negative); 

        void invertType();
        bool updatePosition() override;
        
        void setTarget(Drawable *target);

        virtual bool checkColision() = 0;

        virtual ~Hitbox();
};

class RectangleHitbox : public Hitbox {
    private: 
        float width, height;
        Rectangle rectangle;
    public: 
        RectangleHitbox(const Point &center,float w, float h, hitboxType t = hitboxType::Negative);

        bool checkColision() override;

        float getWidth();
        float getHeight();

        float *getVertices();

};

class PolygonHitbox : public Hitbox {
    private:
        int sides;
        RegularPolygon polygon;
    public:
        PolygonHitbox(const Point&center,int n, float EdgeLength, hitboxType t = hitboxType::Negative);

        bool checkColision() override;

        int getSideCount();
        float getEdgeLength();

        float *getVertices();
};









#endif