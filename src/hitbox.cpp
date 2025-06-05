#include "hitbox.hpp"

Hitbox::Hitbox(float pX, float pY, hitboxType t):
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

RectangleHitbox::RectangleHitbox(float pX, float pY,
                                float w, float h, hitboxType t):
    Hitbox::Hitbox(pX,pY,t), width(w), height(h) {
    
    vertex[0] = {this->getPosX() - width/2, this->getPosY() - height/2};
    vertex[1] = {this->getPosX() + width/2, this->getPosY() + height/2};
    }

bool RectangleHitbox::checkColision() {
    return false;
} //placeholder

float RectangleHitbox::getWidth() {return this->width;}
float RectangleHitbox::getHeight() {return this->height;}
Point RectangleHitbox::getVertex0() {return this->vertex[0];}
Point RectangleHitbox::getVertex1() {return this->vertex[1];}

CircleHitbox::CircleHitbox(float pX, float pY, 
                                float r, hitboxType t):
    Hitbox::Hitbox(pX,pY,t), radius(r) {}
