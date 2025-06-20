#ifndef PASSIVE_H
#define PASSIVE_H

#include "game_object.hpp"
#include <vector>


class Background : public Drawable {
    private:
        ALLEGRO_BITMAP * image = nullptr;
        float width, height;
    public:
        Background(const char* dir,const Point& pos,float w, float h,float speedX);

        virtual ~Background();

        void updateSpeed() override;
        bool updatePosition() override;

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
















#endif