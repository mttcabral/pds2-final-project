#include "entity.hpp"

Entity::Entity(double x, double y, double sX, double sY):
    Drawable::Drawable(x,y,sX,sY) {}
Entity::Entity(double x, double y):
    Entity::Entity(x,y,0,0) {}

Hitbox * Entity::getHitbox() {return this->hb;}

BasicPlayer::BasicPlayer(): Entity::Entity(X_AXIS,400,0,10) {
    hb = new RectangleHitbox(xAxis,400,lengthSize,lengthSize, hitboxType::Positive);
    hb->setTarget(this);
}

BasicPlayer::~BasicPlayer() {
    delete hb;
}

RectangleHitbox *BasicPlayer::getHitboxAABB() {return (RectangleHitbox*) this->getHitbox();}

bool BasicPlayer::updatePosition() {
    if (this->getPosX() != this->xAxis)
        this->setPosX(this->getPosX() + this->getSpeedX());
    this->setPosY(this->getPosY() + this->getSpeedY());
    return true;
}

void BasicPlayer::updateSpeed() {
    if (this->getSpeedX() < 0) this->setSpeedX(0);
    else if (this->getSpeedX() >= 0) this->addSpeedX(-5);

    if (this->getSpeedY() < BASE_GRAVITY) this->addSpeedY(5);
    else if (this->getSpeedY() > BASE_GRAVITY) this->setSpeedY(BASE_GRAVITY);

}

void BasicPlayer::jump() {
    this->addSpeedY(-50);
}

void BasicPlayer::draw() {
    al_draw_filled_rectangle(this->getPosX()-this->lengthSize/2, this->getPosY()-this->lengthSize/2,
                            this->getPosX()+this->lengthSize/2, this->getPosY()+this->lengthSize/2,
                            al_map_rgb(50,100,200)
                            );
}