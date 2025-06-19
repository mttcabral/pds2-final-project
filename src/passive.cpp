#include "passive.hpp"
#include <allegro5/allegro.h>

Background::Background(const char* dir,const Point& pos,float w, float h,float speedX) :
    Drawable::Drawable(pos,Point(speedX,0)), width(w), height(h) {
        image = al_load_bitmap(dir);
        if (!image) throw(std::runtime_error("failed to load image"));
    }

Background::~Background() {
    if (image) al_destroy_bitmap(image);
}

void Background::updateSpeed() {return;}

//the timing is not perfect at all, fix later
bool Background::updatePosition() {
    if (this->getPosX() <= -this->width/2) this->setPosX(1100 + this->width/2); //placeholder?
    else {
        this->setPosX(this->getPosX() + this->getSpeedX());
    }
    return true;
}

void Background::draw() {
    if (image) {
        al_draw_rotated_bitmap(image,width/2,height/2,
        this->getPosX(),this->getPosY(), 0, 0);
    }
}