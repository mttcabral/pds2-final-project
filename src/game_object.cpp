#include "game_object.hpp"

GameObject::GameObject(const Point &position): pos(position) {}
GameObject::GameObject(float pX, float pY): 
    pos(Point(pX,pY)) {}


void GameObject::setPosX(float x) {this->pos.x = x;}
void GameObject::setPosY(float y) {this->pos.y = y;}

Point GameObject::getPos() {return this->pos;}
float GameObject::getPosX() {return this->pos.x;}
float GameObject::getPosY() {return this->pos.y;}

Drawable::Drawable(float x, float y, float sX, float sY):
    GameObject::GameObject(x,y), speedX(sX), speedY(sY) {}
Drawable::Drawable(float x, float y):
    Drawable::Drawable(x,y,0,0) {}

float Drawable::getSpeedX() {return this->speedX;}
float Drawable::getSpeedY() {return this->speedY;}

void Drawable::setSpeedX(float x) {this->speedX = x;}
void Drawable::setSpeedY(float y) {this->speedY = y;}

void Drawable::addSpeedX(float x) {
    this->speedX += x;
}
void Drawable::addSpeedY(float y) {
    this->speedY += y;
}