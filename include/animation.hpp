#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <iostream>

#include <allegro5/allegro.h>

using namespace std;

const float ANIM_FPS = 24;

class Spritesheet {
    protected:
        ALLEGRO_BITMAP * sheet = nullptr;
        int frameCount, frameWidth, frameHeight, frameGap;
        int currentIndex = 0;
        vector<ALLEGRO_BITMAP*> frames;
    public:

        Spritesheet(const char* dir, int count, int frameW, int frameH, int gap);
        Spritesheet(const char* dir, int count, int frameW, int gap);

        //void loadBitmap(const char* dir);

        ALLEGRO_BITMAP * getSheet() const;
        int getFrameCount() const;
        int getFrameWidth() const;
        int getFrameHeight() const;
        int getCurrentIndex() const;
        ALLEGRO_BITMAP * getFrame(int i) const;

        ALLEGRO_BITMAP * getCurrentFrame() const;

        virtual void resetAnimation();

        virtual void advanceFrame();

        ~Spritesheet();


};

class TriggerSpritesheet : public Spritesheet {
    private:
        bool active = false;
        int cycles = 1;
        int currentCycle = 0;
    public:
        TriggerSpritesheet(const char* dir, int count, int frameW, int frameH, int gap);
        TriggerSpritesheet(const char* dir, int count, int frameW, int gap);

        void setCycleCount(int n);
        int getCycleCount() const;

        void resetAnimation() override;

        void advanceFrame() override;

        bool isActive() const;

};














#endif