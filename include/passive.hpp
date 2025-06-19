#ifndef PASSIVE_H
#define PASSIVE_H

#include "game_object.hpp"


class Background : public Drawable {
    private:
        ALLEGRO_BITMAP * image = nullptr;
        float width, height;
    public:
        Background(const char* dir,const Point& pos,float w, float h,float speedX);

        ~Background();

        void updateSpeed() override;
        bool updatePosition() override;

        void draw() override;



};
















#endif