#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.hpp"
#include "hitbox.hpp"
#include "animation.hpp"
#include "cooldown.hpp"
#include <string>

const float BASE_GRAVITY = 10;
const float BASE_X_MOVEMENT = 20;
const float X_AXIS = 160;

//Interactable game object
//Has a hitbox atribute always so its interactable
class Entity: public Drawable {
    protected:
        Hitbox * hb;
    public: 
        Entity(const Point&pos, const Point&spd);
        Entity(const Point&pos);
        Hitbox *getHitbox();
        virtual ~Entity();
};

const float PLAYER_SIZE = 20;

enum class PlayerState {NONE, DEAD, IDLE, JUMPING};

//Basic player class proof of concept
//good if other more well baked versions are created that don't rely on this one
class Player: public Entity {
    private: 
        Spritesheet idleSprite;
        TriggerSpritesheet jumpSprite;
        PlayerState state = PlayerState::NONE;
        
        Cooldown angleCD;
        float angle;
    public: 
        Player();

        bool updatePosition() override;
        void updateSpeed() override;

        void jump();

        void draw() override;

        //bool loadSprite(const char* dir);
        void updatePlayerState();
        void updateAnimation();
        void setPlayerState(PlayerState s);

        ~Player();

};

const float PIPE_X_SPEED = -10;

//Basic obstacle proof of concept, best to not use if possible
class Pipe: public Entity {
    private:
        ALLEGRO_BITMAP * pipeSprite = nullptr;
    public:
        Pipe(const Point&pos,float w, float h);

        bool updatePosition() override;
        void updateSpeed() override;

        bool loadSprite();

        void draw() override;

        ~Pipe();
};
/*
class Eel: public Entity {
    private:
        Spritesheet idleSprite;
    public:
        Eel(int x);

        bool updatePosition() override;
        void updateSpeed() override;
        void updateAnimation();

        void draw() override;

        ~Eel();

};
*/





#endif