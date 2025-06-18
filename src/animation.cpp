#include "animation.hpp"

Spritesheet::Spritesheet(const char* dir, int count, int frameW, int frameH): frameCount(count), frameWidth(frameW), frameHeight(frameH) {
    this->sheet = al_load_bitmap(dir);
    if (!sheet) throw(std::logic_error("failed to load bitmap"));

    for (int i = 0; i < this->frameCount; i++) {
        this->frames.push_back(al_create_sub_bitmap(this->sheet,i*this->frameWidth,0,this->frameWidth,this->frameHeight));
    }
}

Spritesheet::Spritesheet(const char* dir, int count, int frameW): frameCount(count), frameWidth(frameW) {
    this->sheet = al_load_bitmap(dir);
    if (!sheet) throw(std::logic_error("failed to load bitmap"));
    this->frameHeight = al_get_bitmap_height(this->sheet);

    for (int i = 0; i < this->frameCount; i++) {
        this->frames.push_back(al_create_sub_bitmap(this->sheet,i*this->frameWidth,0,this->frameWidth,this->frameHeight));
    }
}

Spritesheet::~Spritesheet() {
    if (sheet) {
        al_destroy_bitmap(sheet);
    }
}


ALLEGRO_BITMAP * Spritesheet::getSheet() const {return this->sheet;}
int Spritesheet::getFrameCount() const {return this->frameCount;}
int Spritesheet::getFrameWidth() const {return this->frameWidth;}
int Spritesheet::getFrameHeight() const {return this->frameHeight;}
int Spritesheet::getCurrentIndex() const {return this->currentIndex;}
ALLEGRO_BITMAP * Spritesheet::getFrame(int i) const {return this->frames[i];}

ALLEGRO_BITMAP * Spritesheet::getCurrentFrame() const {
    return this->frames[currentIndex];
}

void Spritesheet::resetAnimation() {
    this->currentIndex = 0;
}

void Spritesheet::advanceFrame() {
    this->currentIndex = (this->currentIndex + 1) % this->frameCount; 
};