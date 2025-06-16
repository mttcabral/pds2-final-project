#ifndef HITBOX_H
#define HITBOX_H

#include "game_object.hpp"

//Father hitbox game object class
//used to determine occupied space in game and interact with other drawables
class Hitbox: public GameObject{
    private:
        //It is important to note that every hitbox is ALWAYS associated with an object and vice versa
        Drawable* target;
    public: 
        Hitbox(const Point& center); 

        bool updatePosition() override;
        
        void setTarget(Drawable *target);

        virtual Polygon getPolygon() = 0;
        virtual float getAngle() = 0;
        virtual void rotateHitbox(float radians) = 0;

        virtual ~Hitbox();
};

//Rectangular hitbox, used when a rectangle with variable W and H are needed as representation
class RectangleHitbox : public Hitbox {
    private: 
        float width, height;
        Rectangle rectangle;
    public: 
        RectangleHitbox(const Point &center,float w, float h);

        //bool checkColision() override;

        float getWidth();
        float getHeight();

        Polygon getPolygon() override;
        float getAngle() override;

        bool updatePosition() override;
        
        void rotateHitbox(float radians) override;
        
        float *getVertices();

};

//Hitbox with a REGULAR polygon shape
class PolygonHitbox : public Hitbox {
    private:
        int sides;
        RegularPolygon polygon;
    public:
        PolygonHitbox(const Point&center,int n, float EdgeLength);

        int getSideCount();
        float getEdgeLength();

        Polygon getPolygon() override;
        float getAngle() override;

        bool updatePosition() override;

        void rotateHitbox(float radians) override;

        float *getVertices();
};









#endif