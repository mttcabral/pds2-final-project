#include "hitbox.hpp"

Hitbox::Hitbox(double pX, double pY, hitboxType t):
    GameObject::GameObject(pX,pY), type(t) {}

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

RectangleHitbox::RectangleHitbox(double pX, double pY,
                                double w, double h, hitboxType t):
    Hitbox::Hitbox(pX,pY,t), width(w), height(h) {}

bool RectangleHitbox::checkColision() {
    return false;
} //placeholder

double RectangleHitbox::getWidth() {return this->width;}
double RectangleHitbox::getHeight() {return this->height;}

CircleHitbox::CircleHitbox(double pX, double pY, 
                                double r, hitboxType t):
    Hitbox::Hitbox(pX,pY,t), radius(r) {}
