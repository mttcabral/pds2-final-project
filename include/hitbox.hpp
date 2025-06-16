#ifndef HITBOX_H
#define HITBOX_H

#include "game_object.hpp"

/*
enum class hitboxType {
    Positive,
    Negative
}; //maybe overload the operator'!' to invert values (?)
*/

class Hitbox: public GameObject{
    private:
        Drawable* target;
    public: 
        Hitbox(const Point& center); 

        bool updatePosition() override;
        
        void setTarget(Drawable *target);

        virtual Polygon getPolygon() = 0;
        virtual float getAngle() = 0;
        virtual void rotateHitbox(float radians) = 0;
        //virtual bool checkColision(); //to remove soon, wont be needed

        virtual ~Hitbox();
};

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