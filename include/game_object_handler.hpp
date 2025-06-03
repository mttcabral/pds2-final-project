#ifndef HANDLER_H
#define HANDLER_H

#include <list>
#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"

using namespace std;

class Handler {
    private:
        list<Drawable*> goodObjects;
        
        list<Drawable*> badObjects;
    public: 
        void addGoodObject(Drawable * good);
        void addBadObject(Drawable * bad);

        Drawable* checkBadColisionAABB(RectangleHitbox *&target);
        ~Handler();
};








#endif