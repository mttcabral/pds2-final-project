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


RectangleHitbox::RectangleHitbox(const Point& center,float w, float h): Hitbox::Hitbox(center),
                                width(w), height(h), rectangle(center,w,h)  {}



float RectangleHitbox::getWidth() {return this->width;}
float RectangleHitbox::getHeight() {return this->height;}
Polygon RectangleHitbox::getPolygon() {return this->rectangle.getPolygon();}

float *RectangleHitbox::getVertices() {return this->rectangle.getPointArray();}

bool RectangleHitbox::updatePosition() {
    Point previous = this->getPos();
    
    Hitbox::updatePosition();

    Point deltaMovement = this->getPos() - previous;

    this->rectangle.updateVertices(deltaMovement);

    return true;
}

PolygonHitbox::PolygonHitbox(const Point&center,int n, float EdgeLength): Hitbox::Hitbox(center),
                            sides(n), polygon(center,n,EdgeLength) {}

int PolygonHitbox::getSideCount() {return sides;}
float PolygonHitbox::getEdgeLength() {return this->polygon.edgeLength;}
float *PolygonHitbox::getVertices() {return this->polygon.getPointArray();}
Polygon PolygonHitbox::getPolygon() {return this->polygon.getPolygon();}

bool PolygonHitbox::updatePosition() {
    Point previous = this->getPos();
    
    Hitbox::updatePosition();

    Point deltaMovement = this->getPos() - previous;

    this->polygon.updateVertices(deltaMovement);
    
    return true;
}
