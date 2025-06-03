#include "game_object.hpp"

GameObject::GameObject(double pX, double pY, double sX, double sY): 
    posX(pX), posY(pY), speedX(sX), speedY(sY) {}

GameObject::GameObject(double pX, double pY): 
    GameObject::GameObject(pX, pY, 0, 0) {}

void GameObject::setPosX(double x) {this->posX = x;}
void GameObject::setPosY(double y) {this->posY = y;}
void GameObject::setSpeedX(double x) {this->speedX = x;}
void GameObject::setSpeedY(double y) {this->speedY = y;}

void GameObject::addSpeedX(double x) {
    this->speedX += x;
}
void GameObject::addSpeedY(double y) {
    this->speedY += y;
}

double GameObject::getPosX() {return this->posX;}
double GameObject::getPosY() {return this->posY;}
double GameObject::getSpeedX() {return this->speedX;}
double GameObject::getSpeedY() {return this->speedY;}