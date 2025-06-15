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
float RectangleHitbox::getAngle() {return this->rectangle.angle;}

float *RectangleHitbox::getVertices() {return this->rectangle.getPointArray();}

bool RectangleHitbox::updatePosition() {
    Point previous = this->getPos(); // (500,400)
    
    Hitbox::updatePosition(); // getPos() -> (490,400)

    Point deltaMovement = this->getPos() - previous; // = (-10,0)

    this->rectangle.updateVertices(deltaMovement); // (300,600) -> (290,600)

    return true;
}

void RectangleHitbox::rotateHitbox(float radians) {this->rectangle.addAngle(radians);}

PolygonHitbox::PolygonHitbox(const Point&center,int n, float EdgeLength): Hitbox::Hitbox(center),
                            sides(n), polygon(center,n,EdgeLength) {}

int PolygonHitbox::getSideCount() {return sides;}
float PolygonHitbox::getEdgeLength() {return this->polygon.edgeLength;}
float *PolygonHitbox::getVertices() {return this->polygon.getPointArray();}
Polygon PolygonHitbox::getPolygon() {return this->polygon.getPolygon();}
float PolygonHitbox::getAngle() {return this->polygon.angle;}

bool PolygonHitbox::updatePosition() {
    Point previous = this->getPos();
    
    Hitbox::updatePosition();

    Point deltaMovement = this->getPos() - previous;

    this->polygon.updateVertices(deltaMovement);
    
    return true;
}

void PolygonHitbox::rotateHitbox(float radians) {this->polygon.addAngle(radians);}
