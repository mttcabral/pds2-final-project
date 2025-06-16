#include "game_object_handler.hpp"

/*
Handler::~Handler() {
    for (auto obj : this->goodObjects) delete obj;
    for (auto obj : this->badObjects) delete obj;
}

void Handler::addGoodObject(Entity* good) {goodObjects.push_front(good);}
void Handler::addBadObject(Entity* bad) {badObjects.push_front(bad);}

bool Handler::isColidingAABB(RectangleHitbox *&a, RectangleHitbox *&b){
    //first AABB edges
    double aLeftEdge = a->getVertex0().x;
    double aRightEdge = a->getVertex1().x;
    double aTopEdge = a->getVertex0().y;
    double aBottomEdge = a->getVertex1().y;
    //second AABB edges
    double bLeftEdge = b->getVertex0().x;
    double bRightEdge = b->getVertex1().x;
    double bTopEdge = b->getVertex0().y;
    double bBottomEdge = b->getVertex1().y;
    //actual colision logic based on edges
    return (aLeftEdge < bRightEdge) and (aRightEdge > bLeftEdge) and
            (aTopEdge < bBottomEdge) and (aBottomEdge > bTopEdge);
}

Entity* Handler::checkBadColisionAABB(RectangleHitbox *&target) {

    for (auto badObj : this->badObjects) {
        RectangleHitbox *badBox = (RectangleHitbox*) badObj->getHitbox();
        if (Handler::isColidingAABB(target,badBox)) {
            return badObj;
        }
    }
    return nullptr;
}

void Handler::drawAll() {
    for (auto good : this->goodObjects) good->draw();
    for (auto bad : this->badObjects) bad->draw();
}
*/
