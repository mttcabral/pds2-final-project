#include "game_object_handler.hpp"

Handler::~Handler() {
    for (auto obj : this->goodObjects) delete obj;
    for (auto obj : this->badObjects) delete obj;
}

void Handler::addGoodObject(Drawable* good) {goodObjects.push_front(good);}
void Handler::addBadObject(Drawable* bad) {badObjects.push_front(bad);}

// Drawable* Handler::checkBadColisionAABB(RectangleHitbox *&target){}