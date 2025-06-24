#include "entity.hpp"
#include <iostream>

Entity::Entity(const Point&pos,const Point&spd):
    Drawable::Drawable(pos,spd) {}
Entity::Entity(const Point&pos):
    Entity::Entity(pos,{0,0}) {}
Hitbox * Entity::getHitbox() {return this->hb;}
Entity::~Entity(){
    delete hb;
}    
Player::Player(): Entity({X_AXIS,400},{0,5}),
idleSprite("assets/player/idle.png",10,50,0), jumpSprite("assets/player/jump.png",10,50,0),
angleCD(0.15) { 
    this->hb = new PolygonHitbox({X_AXIS,400},8,PLAYER_SIZE);
    this->hb->setTarget(this);
}

bool Player::updatePosition() {
    if (this->getPosX() != X_AXIS)
        this->setPosX(this->getPosX() + this->getSpeedX());
    this->setPosY(this->getPosY() + this->getSpeedY());
    
    this->hb->updatePosition();

    return true;

}
void Player::updateSpeed() {
    if (this->getSpeedX() < 0) this->setSpeedX(0);
    else if (this->getSpeedX() >= 0) this->addSpeedX(-5);

    if (this->getSpeedY() <= BASE_GRAVITY) this->addSpeedY(5);
    else if (this->getSpeedY() > BASE_GRAVITY) this->setSpeedY(BASE_GRAVITY);

}

void Player::jump() {
    this->setSpeedY(-35);
    this->state = PlayerState::JUMPING;
    this->jumpSprite.resetAnimation();
}

void Player::draw() {
    Spritesheet * current = &this->idleSprite;
    switch (this->state) {
        case PlayerState::NONE:
            break;
        case PlayerState::DEAD:
            break;
        case PlayerState::IDLE:
            break;
        case PlayerState::JUMPING:
            current = &this->jumpSprite;
            break;
    }
    al_draw_scaled_rotated_bitmap(
            current->getCurrentFrame(),
            al_get_bitmap_width(current->getCurrentFrame())/2,
            al_get_bitmap_height(current->getCurrentFrame())/2,
            this->getPosX(),this->getPosY(),
            1.3,1.3, 
            this->angle,0);
}

void Player::updateAnimation() {
    switch (this->state) {
        case PlayerState::IDLE:
            this->idleSprite.advanceFrame();
            break;
        case PlayerState::JUMPING:
            if (this->jumpSprite.isActive()) this->jumpSprite.advanceFrame();
            else this->idleSprite.resetAnimation(); //maybe not necessary
            break;
        case PlayerState::NONE:
            break;
        case PlayerState::DEAD:
            break;
        //other states....
    }
}

void Player::updatePlayerState() {
    this->angleCD.updateCooldown();
    
    switch (this->state) {
        case PlayerState::NONE:
            this->state = PlayerState::IDLE;
            this->angle = -PI/8;
            this->angleCD.restartCooldown();
        case PlayerState::IDLE:
            if (this->angleCD.isCooldownUp()) {
                this->angle = PI/4 - PI/8;
            }else {
                float percent = 1 - angleCD.getCurrentPorcentage();
                this->angle = -PI/8 + (PI/4)*percent;
            }
            break;
        case PlayerState::JUMPING:
            this->angle = -PI/8;
            if (!this->jumpSprite.isActive()) {
                this->idleSprite.resetAnimation();
                this->state = PlayerState::IDLE;
                this->angleCD.restartCooldown();
            }
            break;
        case PlayerState::DEAD:
            break;
        //other states.........
    }
}
//SUBJECT TO CHANGE: maybe implement player states based on cooldowns of actions
//CURRENTLY: it is based on animation frames of TriggerSpritesheet being active or not

void Player::setPlayerState(PlayerState s) {this->state = s;}

Player::~Player() {
    //spritesheets already handles destruction correctly
}

Pipe::Pipe(const Point&pos,float w, float h): Entity(pos,Point(PIPE_X_SPEED,0)) { //(-2,0)
    loadSprite();
    this->hb = new RectangleHitbox(pos,w,h);
    this->hb->setTarget(this);
}

Pipe::~Pipe() {
    if (pipeSprite != nullptr) {
        al_destroy_bitmap(pipeSprite);
        pipeSprite = nullptr;
    }
}

bool Pipe::updatePosition() {

    //this->setPos(this->getSpeed() + this->getPos());
    this->setPosX(this->getSpeedX() + this->getPosX());
    this->hb->updatePosition();
    return true;
}
void Pipe::updateSpeed() {
    return; //this basic pipe shoudn't accelerate 
}

bool Pipe::loadSprite(){
        pipeSprite = al_load_bitmap("assets/long.png");
    if (!pipeSprite) {
        std::cout << "SPRITE LOADING FAILED FOR PIPE\n";
        return false;
    }else return true;
}

void Pipe::draw() {
    if (!pipeSprite) {
        std::cout << "NO SPRITE LOADED FOR PIPE\n";
        return;
    }
    al_draw_rotated_bitmap(pipeSprite,
                            al_get_bitmap_width(pipeSprite)/2,al_get_bitmap_height(pipeSprite)/2,
                            this->getPosX(), this->getPosY(),this->getHitbox()->getAngle(),0);              
}
/*Eel::Eel(int x): Entity({1000,300},Point(PIPE_X_SPEED,0)),
idleSprite("assets/player/long.png",10,50,0) { 
    this->hb = new RectangleHitbox({1000,300},50,375+x);
    this->hb->setTarget(this);
};
void Eel::updateAnimation(){
    this->idleSprite.advanceFrame();
};
void Pipe::updateSpeed() {
    return;
};
bool Eel::updatePosition(){
    this->setPosX(this->getSpeedX() + this->getPosX());
    this->hb->updatePosition();
    return true;
};
void Eel::draw(){
    al_draw_scaled_rotated_bitmap(
            current.getCurrentFrame(),
            al_get_bitmap_width(current->getCurrentFrame())/2,
            al_get_bitmap_height(current->getCurrentFrame())/2,
            this->getPosX(),this->getPosY(),
            1.3,1.3, 
            0,0);
}
*/