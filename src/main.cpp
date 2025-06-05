#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"
#include "initializer_allegro.hpp"
#include "game_object_handler.hpp"
#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

// Game constants:
const float FPS = 30;                                        // Frames per second
const int SCREEN_W = 800;                                    // Screen width in pixels
const int SCREEN_H = 600;                                    // Screen height in pixels
const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);  // Background color (black)

int main(){

    // Basic Allegro pointers:
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *eventQueue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    
    // Initializations:
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

    // Basic player object for testing
    BasicPlayer squareGuy;

    ALLEGRO_COLOR baseBackgroundColor = al_map_rgba_f(1,1,1,1);

    float Tvertices[5][2] = {{100,100},{200,200},{100,0},{0,100},{300,150}};

    while (gameActive) {
        
        ALLEGRO_EVENT event;

        al_wait_for_event(eventQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                //refresh display
                al_clear_to_color(baseBackgroundColor); //white color 

                squareGuy.updateSpeed();
                squareGuy.updatePosition();
                
                squareGuy.draw();
                al_draw_filled_polygon(&Tvertices[0][0], 5, al_map_rgb(255, 0, 0));

                al_flip_display(); //updates the display with the new frame 

            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_SPACE: case ALLEGRO_KEY_UP:
                        squareGuy.jump();
                }

            break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                gameActive = false;
            break;
        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    al_destroy_timer(timer);
    return 0;
}