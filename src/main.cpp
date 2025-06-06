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
const int SCREEN_W = 1000;                                    // Screen width in pixels
const int SCREEN_H = 800;                                    // Screen height in pixels
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
    //BasicPlayer squareguy;
    Player guy;
    guy.loadSprite("assets/guy.png");
    // Basic obstacle object for testing
    Pipe obstacle(Point(1000,400),128,128);
    //Pipe obstacle(Point(200,600),128,128);
    obstacle.loadSprite("assets/pipe.png");

    ALLEGRO_COLOR baseBackgroundColor = al_map_rgba_f(1,1,1,1);

    //RegularPolygon hexagon(Point(200,400),6,100);
    //float * vertexList = hexagon.getPointArray();
    

    /*
    const int num_points = 4;
    float points[] = {
        100.0f, 100.0f,  // Point 1 (x, y)
        100.0f, 500.0f,   // Point 2
        500.0f, 500.0f,  // Point 3
        500.0f, 100.0f   // Point 4
    };
    */

    while (gameActive) {
        
        ALLEGRO_EVENT event;

        al_wait_for_event(eventQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                //refresh display
                al_clear_to_color(baseBackgroundColor); //white color 

                guy.updateSpeed();
                guy.updatePosition();
                obstacle.updateSpeed();
                //cout << obstacle.getPosX() << '\n';
                obstacle.updatePosition();
                
                if (isColidingSAT(guy.getHitbox()->getPolygon(),obstacle.getHitbox()->getPolygon())){
                    //baseBackgroundColor = al_map_rgba_f(0.5,0.5,0.5,1);
                    //cout << "AAAAA";
                    al_draw_filled_circle(800,400,30,al_map_rgb(140,20,20));
                }else {
                    al_draw_filled_circle(800,400,30,al_map_rgb(20,140,20));
                }//cout << "...";
                //al_draw_filled_rectangle(100,100,500,500,al_map_rgb(255,0,0));
                //al_draw_filled_polygon(points, num_points, al_map_rgb(255, 0, 0));
                //al_draw_filled_polygon(vertexList, 5, al_map_rgb(255, 0, 0));
                guy.draw();
                obstacle.draw();
                

                al_flip_display(); //updates the display with the new frame 

            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_SPACE: case ALLEGRO_KEY_UP:
                        guy.jump();
                        //squareguy.jump();
                        cout << "Jump\n";
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
    
    //delete[] vertexList;


    return 0;
}