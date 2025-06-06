#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.hpp"
#include "hitbox.hpp"
#include <string>

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

const float PLAYER_SIZE = 1;

class Player: public Entity {
    private: 
        ALLEGRO_BITMAP * playerSprite = nullptr;
    public: 
        Player();

        bool updatePosition() override;
        void updateSpeed() override;

        void jump();

        void draw() override;

        bool loadSprite(const char* dir);

        ~Player();

};

class Pipe: public Entity {
    private:
        ALLEGRO_BITMAP * pipeSprite = nullptr;
    public:
        Pipe(const Point&pos,float w, float h);

        bool updatePosition() override;
        void updateSpeed() override;

        bool loadSprite(const char* dir);

        void draw() override;

        ~Pipe();
};

//implement entities with PolygonHitbox now










#endif