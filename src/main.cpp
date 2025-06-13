#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"
#include "initializer_allegro.hpp"
#include "game_object_handler.hpp"
#include "cooldown.hpp"
#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

// Game constants:
// const float FPS = 30;                                      // Frames per second (in cooldown.hpp)
const int SCREEN_W = 1000;                                    // Screen width in pixels
const int SCREEN_H = 800;                                     // Screen height in pixels
const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);   // Background color (black)

int main(){

    // Basic Allegro pointers:
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *eventQueue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    
    // Initializations:

    //V-Sync:
    //tries to solve frame-skipping bug, still not solved !!!
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

    if(!initialize_allegro()) return 1;

    if(!initialize_event_queue(eventQueue)) return 1;

    if(!initialize_display_and_timer(display,SCREEN_W,SCREEN_H,timer,FPS)) return 1;

    // Register event sources for the event queue
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    // Start the timer to control game speed
    al_start_timer(timer);

    // Game is being played control
    bool gameActive = true;
    
    //Redraw condition, so that the game is rendered separately from other events in queue
    bool redraw = false;

    ALLEGRO_COLOR colisionIndicatorColor = al_map_rgb(20,140,20);

    // Basic player object for testing
    //BasicPlayer squareguy;
    Player guy;
    guy.loadSprite("assets/guy.png");
    // Basic obstacle object for testing
    Pipe obstacle(Point(1000,400),128,128);
    //Pipe obstacle(Point(200,600),128,128);
    obstacle.loadSprite("assets/pipe.png");

    ALLEGRO_COLOR baseBackgroundColor = al_map_rgba_f(0.7,0.7,0.9,1);
    

    while (gameActive) {
        
        ALLEGRO_EVENT event;

        al_wait_for_event(eventQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:

                guy.updateSpeed();
                guy.updatePosition(); 
                obstacle.updateSpeed();
                obstacle.updatePosition();
                
                if (isColidingSAT(guy.getHitbox()->getPolygon().getPolygon(),
                                obstacle.getHitbox()->getPolygon().getPolygon())){
                    colisionIndicatorColor = al_map_rgb(140,20,20);
                }else {
                    colisionIndicatorColor = al_map_rgb(20,140,20);
                } //placeholder colision detection and visualization
                
                redraw = true;

            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_SPACE: case ALLEGRO_KEY_UP:
                        guy.jump();
                        //cout << "Jump\n";
                        break;
                    }
            break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                gameActive = false;
            break;
        }

        //redraw frame
        if (redraw && al_is_event_queue_empty(eventQueue)) {
            //refresh display
            al_clear_to_color(baseBackgroundColor);

            //objects
            guy.draw();
            obstacle.draw();

            //colision
            al_draw_filled_circle(800,400,30,colisionIndicatorColor); 

            al_flip_display(); //updates the display with the new frame 

            redraw = false;
        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    al_destroy_timer(timer);
    
    //delete[] vertexList;


    return 0;
}