#ifndef PASSIVE_H
#define PASSIVE_H

#include "game_object.hpp"
#include "cooldown.hpp"
#include <vector>


class Background : public Drawable {
    protected:
        ALLEGRO_BITMAP * image = nullptr;
        float width, height;
    public:
        Background(const char* dir,const Point& pos,float w, float h,float speedX);

        virtual ~Background();

        void updateSpeed() override;
        bool updatePosition() override;
        ALLEGRO_BITMAP * getImage() {return this->image;}

        void draw() override;

        friend class BackgroundHandler;
};

class BackgroundHandler {
    private:
        std::vector<Background*> bgPair;
        float screenWidth,screenHeight;
        Point anchor;
    public:
        BackgroundHandler(const char*dir,float w, float h, 
                            float speedX, float screenW, float screenH);

        ~BackgroundHandler();

        void drawBackground();
        void updateBackgroundPosition();
};
enum class tStage {NONE, FIRST_HALF, SECOND_HALF};

const Point T_ANCHOR(400,950);
const float T_SPEED = 18;
const float T_TIME = (750/(T_SPEED*FPS));

class TransitionScreen: public Background {
    private:
        Cooldown cd;
        tStage stage = tStage::NONE;
    public:
        TransitionScreen();

        void updateSpeed() override;
        bool updatePosition() override;
        
        void draw() override;

        void updateStage();

        void startTransition();


        bool isActive();
        tStage getStage();
};















#endif