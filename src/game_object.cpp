#include "game_object.hpp"

GameObject::GameObject(const Point &position): pos(position) {}
GameObject::GameObject(float pX, float pY): 
    pos(Point(pX,pY)) {}


void GameObject::setPosX(float x) {this->pos.x = x;}
void GameObject::setPosY(float y) {this->pos.y = y;}
void GameObject::setPos(const Point& p) {this->pos = p;}

Point GameObject::getPos() {return this->pos;}
float GameObject::getPosX() {return this->pos.x;}
float GameObject::getPosY() {return this->pos.y;}

Drawable::Drawable(const Point&pos,const Point&spd):
    GameObject::GameObject(pos), speed(spd) {}
Drawable::Drawable(const Point&pos):
    Drawable::Drawable(pos,{0,0}) {}

float Drawable::getSpeedX() {return this->speed.x;}
float Drawable::getSpeedY() {return this->speed.y;}
Point Drawable::getSpeed()  {return this->speed;}

void Drawable::setSpeedX(float x) {this->speed.x = x;}
void Drawable::setSpeedY(float y) {this->speed.y = y;}
void Drawable::setSpeed(const Point&spd) {this->speed = spd;}

void Drawable::addSpeedX(float x) {
    this->speed.x += x;
}
void Drawable::addSpeedY(float y) {
    this->speed.y += y;
}
void Drawable::addSpeedVector(const Point&spd){
    this->speed = this->speed + spd;
}