#include "entity.hpp"
#include <iostream>

Entity::Entity(const Point&pos,const Point&spd):
    Drawable::Drawable(pos,spd) {}
Entity::Entity(const Point&pos):
    Entity::Entity(pos,{0,0}) {}

Hitbox * Entity::getHitbox() {return this->hb;}

BasicPlayer::BasicPlayer(): Entity::Entity(Point(X_AXIS,400),Point(0,10)) {
    hb = new RectangleHitbox({xAxis,400},lengthSize,lengthSize);
    hb->setTarget(this);
    //cout << "speed " << this->getSpeed() << '\n'; 
}

BasicPlayer::~BasicPlayer() {
    delete hb;
}

RectangleHitbox *BasicPlayer::getHitboxAABB() {return (RectangleHitbox*) this->getHitbox();}

bool BasicPlayer::updatePosition() {
    if (this->getPosX() != this->xAxis)
        this->setPosX(this->getPosX() + this->getSpeedX());
    this->setPosY(this->getPosY() + this->getSpeedY());
    
    this->hb->updatePosition();

    return true;
}

void BasicPlayer::updateSpeed() {
    if (this->getSpeedX() < 0) this->setSpeedX(0);
    else if (this->getSpeedX() >= 0) this->addSpeedX(-5);

    if (this->getSpeedY() < BASE_GRAVITY) this->addSpeedY(5);
    else if (this->getSpeedY() >= BASE_GRAVITY) this->setSpeedY(BASE_GRAVITY);

}

void BasicPlayer::jump() {
    this->setSpeedY(-40);
}

void BasicPlayer::draw() {
    al_draw_filled_rectangle(this->getPosX()-this->lengthSize/2, this->getPosY()-this->lengthSize/2,
                            this->getPosX()+this->lengthSize/2, this->getPosY()+this->lengthSize/2,
                            al_map_rgb(50,100,200)
                            );
}



Player::Player(): Entity({X_AXIS,400},{0,5}) {
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

    
    /*
    if (this->getSpeedY() < BASE_GRAVITY) {
        if (this->getSpeedY() <= 0) {
            this->addSpeedY(7.5);
        } else this->addSpeedY(5);
    }
    */
    if (this->getSpeedY() <= BASE_GRAVITY) this->addSpeedY(5);
    else if (this->getSpeedY() > BASE_GRAVITY) this->setSpeedY(BASE_GRAVITY);

}

void Player::jump() {
    this->setSpeedY(-35);
}

bool Player::loadSprite(const char* dir) {
    playerSprite = al_load_bitmap(dir);
    if (!playerSprite) {
        std::cout << "SPRITE LOADING FAILED FOR PLAYER\n";
        return false;
    }else return true;
}

void Player::draw() {
    if (!playerSprite) {
        std::cout << "NO SPRITE LOADED FOR PLAYER\n";
        return;
    }
    al_draw_rotated_bitmap(playerSprite,
                            al_get_bitmap_width(playerSprite)/2,al_get_bitmap_width(playerSprite)/2,
                            this->getPosX(), this->getPosY(),0,0);
}

Player::~Player() {
    if (playerSprite) al_destroy_bitmap(playerSprite);
    playerSprite = nullptr;
}

Pipe::Pipe(const Point&pos,float w, float h): Entity(pos,Point(PIPE_X_SPEED,0)) { //(-2,0)
    this->hb = new RectangleHitbox(pos,w,h);
    this->hb->setTarget(this);
}

Pipe::~Pipe() {
    if (pipeSprite) al_destroy_bitmap(pipeSprite);
    pipeSprite = nullptr;
}

bool Pipe::updatePosition() {

    //this->setPos(this->getSpeed() + this->getPos());
    this->setPosX(this->getSpeedX() + this->getPosX());
    if (this->getPosX() < -200) this->setPosX(1000); // placeholder !!!!!
    this->hb->updatePosition();
    return true;
}
void Pipe::updateSpeed() {
    return; //this basic pipe shoudn't accelerate 
}

bool Pipe::loadSprite(const char* dir){
        pipeSprite = al_load_bitmap(dir);
    if (!pipeSprite) {
        std::cout << "SPRITE LOADING FAILED FOR PLAYER\n";
        return false;
    }else return true;
}

void Pipe::draw() {
    if (!pipeSprite) {
        std::cout << "NO SPRITE LOADED FOR PLAYER\n";
        return;
    }
    al_draw_rotated_bitmap(pipeSprite,
                            al_get_bitmap_width(pipeSprite)/2,al_get_bitmap_width(pipeSprite)/2,
                            this->getPosX(), this->getPosY(),0,0);
}
