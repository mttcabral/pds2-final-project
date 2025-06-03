#include "game_object.hpp"

GameObject::GameObject(double pX, double pY): 
    pos(pX,pY) {}


void GameObject::setPosX(double x) {this->pos.x = x;}
void GameObject::setPosY(double y) {this->pos.y = y;}

Point GameObject::getPos() {return this->pos;}
double GameObject::getPosX() {return this->pos.x;}
double GameObject::getPosY() {return this->pos.y;}

Drawable::Drawable(double x, double y, double sX, double sY):
    GameObject::GameObject(x,y), speedX(sX), speedY(sY) {}
Drawable::Drawable(double x, double y):
    Drawable::Drawable(x,y,0,0) {}

double Drawable::getSpeedX() {return this->speedX;}
double Drawable::getSpeedY() {return this->speedY;}

void Drawable::setSpeedX(double x) {this->speedX = x;}
void Drawable::setSpeedY(double y) {this->speedY = y;}

void Drawable::addSpeedX(double x) {
    this->speedX += x;
}
void Drawable::addSpeedY(double y) {
    this->speedY += y;
}