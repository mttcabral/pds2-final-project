#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.hpp"
#include "hitbox.hpp"

const float BASE_GRAVITY = 10;
const float BASE_X_MOVEMENT = 20;
const float X_AXIS = 200;

class Entity: public Drawable {
    protected:
        Hitbox * hb;
    public: 
        Entity(const Point&pos, const Point&spd);
        Entity(const Point&pos);

        Hitbox *getHitbox();
};

class BasicPlayer: public Entity {
    private:
        float xAxis = X_AXIS;
        float lengthSize = 100;
    public:
        BasicPlayer();

        RectangleHitbox *getHitboxAABB();

        bool updatePosition() override;
        void updateSpeed() override;

        void jump();

        void draw() override;
        
        ~BasicPlayer();
};

//implement entities with PolygonHitbox now










#endif