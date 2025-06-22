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
    this->setPosX(this->getPosX() + this->getSpeedX());
    /*
    if (this->getPosX() <= -this->width/2) this->setPosX(1100 + this->width/2); //placeholder?
    else {
        this->setPosX(this->getPosX() + this->getSpeedX());
    }
    */
    return true;
}

void Background::draw() {
    if (image) {
        al_draw_rotated_bitmap(image,width/2,height/2,
        this->getPosX(),this->getPosY(), 0, 0);
    }
}

//Point a = (0 + w/2, screenH - h/2)

BackgroundHandler::BackgroundHandler(const char*dir, float w, float h,
                                     float speedX, float screenW, float screenH) :
    screenWidth(screenW), screenHeight(screenH), anchor(Point(w/2, screenH - h/2)) {
        bgPair.push_back(new Background(dir, anchor, w, h, speedX));
        bgPair.push_back(new Background(dir, anchor + Point(w,0), w, h, speedX));
    }

BackgroundHandler::~BackgroundHandler() {
    for (auto&bg: bgPair) delete bg; 
}


void BackgroundHandler::drawBackground() {
    for (auto &bg : bgPair) {
        al_draw_rotated_bitmap(bg->image,bg->width/2, bg->height/2,
                                bg->getPosX(), bg->getPosY(), 0 , 0);
    }
}

void BackgroundHandler::updateBackgroundPosition() {
    for (auto& bg: bgPair) {
        bg->updatePosition();
    }
    if (bgPair[0]->getPosX() <= -bgPair[0]->width/2) {
        bgPair[0]->setPosX(bgPair[1]->getPosX() + bgPair[1]->width);
    }else if (bgPair[1]->getPosX() <= -bgPair[1]->width/2) {
        bgPair[1]->setPosX(bgPair[0]->getPosX() + bgPair[0]->width);
    }
}


TransitionScreen::TransitionScreen(): Background::Background("assets/bg/transition.png",T_ANCHOR,
                                                            800,1200,0), cd(T_TIME) {
                                                                if (!image) cout << "error";
                                                            }
 
                                                         
void TransitionScreen::updateSpeed() {
    switch (this->stage) {
        case tStage::NONE:

            break;
        case tStage::FIRST_HALF:
            this->setSpeedY(-T_SPEED);
            break;
        case tStage::SECOND_HALF:
            this->setSpeedY(T_SPEED);
            break;
    }
}

void TransitionScreen::draw() {  
    //cout << "aaaa\n";
    al_draw_rotated_bitmap(image,width/2,height/2,this->getPosX(),this->getPosY(),0,0);
}

void TransitionScreen::updateStage() {
    cd.updateCooldown();

    switch (this->stage) {
        case tStage::NONE:
            break;
        case tStage::FIRST_HALF:
            if (cd.isCooldownUp()) {
                stage = tStage::SECOND_HALF;
                cd.restartCooldown();
            }
            break;
        case tStage::SECOND_HALF:
            if (cd.isCooldownUp()) {
                stage = tStage::NONE;
                this->setPos(T_ANCHOR);
            }
            break;
    }
}

bool TransitionScreen::updatePosition() {
    switch (this->stage) {
        case tStage::NONE:
            break;
        case tStage::FIRST_HALF: case tStage::SECOND_HALF:
            this->setPosY(this->getPosY() + this->getSpeedY());
            //cout << this->getPos() << '\n';
            break;
    }
    return true;
}

bool TransitionScreen::isActive() {
    if (stage == tStage::NONE) return false;
    else return true;
}
tStage TransitionScreen::getStage() {return this->stage;}

void TransitionScreen::startTransition() {
    stage = tStage::FIRST_HALF;
    cd.restartCooldown();
    this->setPos(T_ANCHOR);
    //cout << "transition\n";
}