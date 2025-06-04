#ifndef HANDLER_H
#define HANDLER_H

#include <list>
#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"

using namespace std;

class Handler {
    private:
        list<Entity*> goodObjects;
        
        list<Entity*> badObjects;
    public: 
        void addGoodObject(Entity * good);
        void addBadObject(Entity * bad);

        Entity* checkBadColisionAABB(RectangleHitbox *&target);

        static bool isColidingAABB(RectangleHitbox *&a, RectangleHitbox *&b);
        ~Handler();
};








#endif