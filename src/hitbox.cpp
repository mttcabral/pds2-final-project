#include "hitbox.hpp"

Hitbox::Hitbox(const Point& center):
    GameObject::GameObject(center){}

Hitbox::~Hitbox() {}



bool Hitbox::updatePosition() {
    if (!this->target) return false;
    
    this->setPosX(target->getPosX());
    this->setPosY(target->getPosY());
    return true;
}

void Hitbox::setTarget(Drawable *d) {this->target = d;}


RectangleHitbox::RectangleHitbox(const Point& center,float w, float h): width(w),
                                height(h), Hitbox::Hitbox(center), rectangle(center,w,h) {}

bool RectangleHitbox::checkColision() {
    return false;
} //placeholder

float RectangleHitbox::getWidth() {return this->width;}
float RectangleHitbox::getHeight() {return this->height;}

float *RectangleHitbox::getVertices() {return this->rectangle.getPointArray();}


PolygonHitbox::PolygonHitbox(const Point&center,int n, float EdgeLength): 
                            sides(n), Hitbox::Hitbox(center), polygon(center,n,EdgeLength) {}

int PolygonHitbox::getSideCount() {return sides;}
float PolygonHitbox::getEdgeLength() {return this->polygon.edgeLength;}
float *PolygonHitbox::getVertices() {return this->polygon.getPointArray();}