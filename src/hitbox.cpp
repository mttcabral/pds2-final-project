#include "hitbox.hpp"

Hitbox::Hitbox(double pX, double pY, hitboxType t = hitboxType::Negative):
    GameObject::GameObject(pX,pY), type(t) {}

void Hitbox::invertType() {
    if (this->type == hitboxType::Positive) this->type = hitboxType::Negative;
    else hitboxType::Positive;
}

void Hitbox::updatePosition(double x, double y) {
    this->setPosX(x);
    this->setPosY(y);
}

RectangleHitbox::RectangleHitbox(double pX, double pY,
                                double w, double h, hitboxType t = hitboxType::Negative):
    Hitbox::Hitbox(pX,pY,t), width(w), height(h) {}

CircleHitbox::CircleHitbox(double pX, double pY, 
                                double r, hitboxType t = hitboxType::Negative):
    Hitbox::Hitbox(pX,pY,t), radius(r) {}
