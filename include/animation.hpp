#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <iostream>

#include <allegro5/allegro.h>

using namespace std;

const float ANIM_FPS = 12;

class Spritesheet {
    private:
        ALLEGRO_BITMAP * sheet = nullptr;
        int frameCount, frameWidth;
        int currentIndex = 0;
        vector<ALLEGRO_BITMAP*> frames;
    public:

        Spritesheet(const char* dir, int count, int frameW);

        void loadBitmap(const char* dir);

        int getSheet() const;
        int getFrameCount() const;
        int getFrameWidth() const;
        int getCurrentIndex() const;
        ALLEGRO_BITMAP getFrame(int i) const;

        ALLEGRO_BITMAP * getCurrentFrame() const;

        void resetAnimation();

        void advanceFrame();




};














#endif