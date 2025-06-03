#include "entity.hpp"

Entity::Entity(double x, double y, double sX, double sY):
    Drawable::Drawable(x,y,sX,sY) {}
Entity::Entity(double x, double y):
    Entity::Entity(x,y,0,0) {}

BasicPlayer::BasicPlayer(): Entity::Entity(xAxis,400,0,10) {
    hb = new RectangleHitbox(xAxis,400,lengthSize,lengthSize, hitboxType::Positive);
    hb->setTarget(this);
}