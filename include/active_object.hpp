#ifndef ACTIVE_H
#define ACTIVE_H

#include "game_object.hpp"
#include "hitbox.hpp"



class ActiveObject: public Drawable {
    protected:
        Hitbox * hb;
};












#endif