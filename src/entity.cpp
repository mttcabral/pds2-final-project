#include "entity.hpp"

Entity::Entity(double x, double y, double sX, double sY):
    Drawable::Drawable(x,y,sX,sY) {}
Entity::Entity(double x, double y):
    Entity::Entity(x,y,0,0) {}

BasicPlayer::BasicPlayer(): Entity::Entity(xAxis,400,0,10) {
    hb = new RectangleHitbox(xAxis,400,lengthSize,lengthSize, hitboxType::Positive);
    hb->setTarget(this);
}

BasicPlayer::~BasicPlayer() {
    delete hb;
}

bool BasicPlayer::updatePosition() {
    this->setPosX(this->getPosX() + this->getSpeedX());
    this->setPosY(this->getPosY() + this->getSpeedY());
    return true;
}

void BasicPlayer::updateVelocity() {
    if (this->getSpeedX() < 0) this->setSpeedX(0);
    else if (this->getSpeedX() >= 0) this->addSpeedX(-5);

    if (this->getSpeedY() < BASE_GRAVITY) this->addSpeedY(5);
    else if (this->getSpeedY() > BASE_GRAVITY) this->setSpeedY(BASE_GRAVITY);

}

void BasicPlayer::jump() {
    this->addSpeedY(-50);
}