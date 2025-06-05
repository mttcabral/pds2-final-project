#include "hitbox.hpp"

Hitbox::Hitbox(const Point& center, hitboxType t):
    GameObject::GameObject(center), type(t) {}

Hitbox::~Hitbox() {}

void Hitbox::invertType() {
    if (this->type == hitboxType::Positive) this->type = hitboxType::Negative;
    else this->type = hitboxType::Positive;
}

bool Hitbox::updatePosition() {
    if (!this->target) return false;
    
    this->setPosX(target->getPosX());
    this->setPosY(target->getPosY());
    return true;
}

void Hitbox::setTarget(Drawable *d) {this->target = d;}


RectangleHitbox::RectangleHitbox(const Point& center,float w, float h, hitboxType t): width(w),
                                height(h), Hitbox::Hitbox(center,t), rectangle(center,w,h) {}

bool RectangleHitbox::checkColision() {
    return false;
} //placeholder

float RectangleHitbox::getWidth() {return this->width;}
float RectangleHitbox::getHeight() {return this->height;}

float *RectangleHitbox::getVertices() {return this->rectangle.getPointArray();}


PolygonHitbox::PolygonHitbox(const Point&center,int n, float EdgeLength, hitboxType t): 
                            sides(n), Hitbox::Hitbox(center,t), polygon(center,n,EdgeLength) {}

int PolygonHitbox::getSideCount() {return sides;}
float PolygonHitbox::getEdgeLength() {return this->polygon.edgeLength;}
float *PolygonHitbox::getVertices() {return this->polygon.getPointArray();}