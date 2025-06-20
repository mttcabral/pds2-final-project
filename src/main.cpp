#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"
#include "initializer_allegro.hpp"
#include "game_object_handler.hpp"
#include "cooldown.hpp"
#include "sound.hpp"
#include <iostream>
#include <string>


using namespace std;

enum GameState {MENU, PLAYING, LEADERBOARD, QUIT}; // Use for in game logic

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
    
    if(!al_is_mouse_installed()) return 1;

    // Register event sources for the event queue
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    // Start the timer to control game speed
    al_start_timer(timer);

    // Start the sample queue
    al_reserve_samples(100);
    
    //Redraw condition, so that the game is rendered separately from other events in queue
    bool redraw = false;

    ALLEGRO_COLOR colisionIndicatorColor = al_map_rgb(20,140,20);

    // Basic player object for testing
    // BasicPlayer squareguy;
    Player guy;
    guy.loadSprite("assets/guy.png");
    // Basic obstacle object for testing
    Pipe obstacle(Point(1000,400),50,300);
    //Pipe obstacle(Point(200,600),128,128);
    obstacle.loadSprite("assets/long.png");

    // loading images and font
    ALLEGRO_BITMAP* menu_background = al_load_bitmap("assets/menu_background.png");
    ALLEGRO_BITMAP* play_button = al_load_bitmap("assets/menu_play_button.png");
    ALLEGRO_BITMAP* quit_button = al_load_bitmap("assets/menu_quit_button.png");
    ALLEGRO_BITMAP* hover_play = al_load_bitmap("assets/menu_hover_play_button.png");
    ALLEGRO_BITMAP* hover_quit = al_load_bitmap("assets/menu__hover_quit_button.png");
    ALLEGRO_FONT* menu_font = al_load_ttf_font("assets/PressStart2P-Regular.ttf", 72, 0);

    // loading music (.wav please)
    ALLEGRO_SAMPLE* menu_music = al_load_sample("assets/HudsonMohawke_Cbat.wav");
    if(!menu_music) std::cerr << "Erro: música menu_music não foi carregada\n";
    ALLEGRO_SAMPLE* playing_music = al_load_sample("assets/Escape_Persona5.wav");
    if(!playing_music) std::cerr << "Erro: música playing_music não foi carregada\n";

    //treating music
    ALLEGRO_SAMPLE_INSTANCE* menu_music_inst  = al_create_sample_instance(menu_music);
    ALLEGRO_SAMPLE_INSTANCE* playing_music_inst = al_create_sample_instance(playing_music);
    // menu music
    startmusic(menu_music_inst, 0.1);
    // playing music
    startmusic(playing_music_inst, 0.1);



    if (!menu_background) std::cerr << "Erro: imagem menu_background não foi carregada!\n";
    if (!play_button)     std::cerr << "Erro: imagem play_button não foi carregada!\n";
    if(!hover_play) std::cerr << "Erro: imagem hover_play não foi carregada \n";
    if (!quit_button)     std::cerr << "Erro: imagem quit_button não foi carregada!\n";
    if(!hover_quit) std::cerr << "Erro: imagem hover_quit não foi carregada\n";
    if(!menu_font) std::cerr << "Erro: fonte menu_font não foi carregada \n";
    

    // seeing if everything is alright
    if(!menu_background || !play_button || !quit_button || !menu_font){
        return 1;
    }
    
 
    //coordinates of play and quit
    int xplay = 350, yplay = 350;
    int xquit = 350, yquit = 650;

    ALLEGRO_COLOR baseBackgroundColor = al_map_rgba_f(0.7,0.7,0.9,1);
    
    //testing cooldown
    Cooldown jumpCD(0);

    //Menu condition
    GameState state = MENU;

    bool Hplay = false, Hquit = false; //variables that detect if the hover effect is playing

    int mousex = -1, mousey = -1;

    if(state == MENU){
        al_play_sample_instance(menu_music_inst);
    }   
    
    while(state == MENU){
        ALLEGRO_EVENT event;

        al_wait_for_event(eventQueue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            mousex = event.mouse.x;
            mousey = event.mouse.y;

            int play_w = al_get_bitmap_width(play_button);
            int play_h = al_get_bitmap_height(play_button);

            int quit_w = al_get_bitmap_width(quit_button);
            int quit_h = al_get_bitmap_height(quit_button);

            Hplay = (mousex>=xplay && mousex <= xplay + play_w && mousey>=yplay && mousey<= yplay + play_h);
            
            Hquit = (mousex>=xquit && mousex <= xquit + quit_w && mousey>=yquit && mousey<= yquit + quit_h);
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(Hplay) state = PLAYING;
            if(Hquit) state = QUIT;
        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            state = QUIT;
        }

        if(redraw && al_is_event_queue_empty(eventQueue)){
            al_clear_to_color(al_map_rgb(0,0,0)); 
            al_draw_bitmap(menu_background, 0, 0, 0);
            al_draw_text(menu_font, al_map_rgb(0,0,0), (SCREEN_W/2) + 5, 260, ALLEGRO_ALIGN_CENTER, "PeiTche!");
            al_draw_text(menu_font, al_map_rgb(255,255,255), (SCREEN_W/2) + 5, 250, ALLEGRO_ALIGN_CENTER, "PeiTche!");

            //implementation of the hover effect
            if(Hplay) {
                al_draw_bitmap(hover_play, xplay, yplay, 0);
            } else {
                al_draw_bitmap(play_button, xplay, yplay, 0);
            }

            if(Hquit) {
                al_draw_bitmap(hover_quit, xquit, yquit, 0);
            } else {
                al_draw_bitmap(quit_button, xquit, yquit, 0);
            }
            
            al_flip_display();

            redraw = false;
        }
    }
    if(state == PLAYING){
        al_stop_sample_instance(menu_music_inst);
        al_play_sample_instance(playing_music_inst);
    }

    while (state == PLAYING) {
        
        ALLEGRO_EVENT event;

        al_wait_for_event(eventQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:

                guy.updateSpeed();
                guy.updatePosition(); 
                obstacle.updateSpeed();
                obstacle.updatePosition();
                
                obstacle.getHitbox()->rotateHitbox(PI/180);

                if (isColidingSAT(guy.getHitbox()->getPolygon(),
                                obstacle.getHitbox()->getPolygon())){
                    colisionIndicatorColor = al_map_rgb(140,20,20);
                }else {
                    colisionIndicatorColor = al_map_rgb(20,140,20);
                } //placeholder colision detection and visualization
                
                redraw = true;

                jumpCD.updateCooldown();
                //cout << jumpCD.getCurrentPorcentage() << '\n';

            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_SPACE: case ALLEGRO_KEY_UP:
                        if (jumpCD.isCooldownUp()) {
                            guy.jump();
                            jumpCD.restartCooldown();
                        }
                        //cout << "Jump\n";
                        break;
                    }
            break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                state = QUIT;
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
    al_destroy_font(menu_font);
    al_destroy_bitmap(menu_background);
    al_destroy_bitmap(play_button);
    al_destroy_bitmap(quit_button);
    al_destroy_bitmap(hover_play);
    al_destroy_bitmap(hover_quit);
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    al_destroy_timer(timer);
    al_destroy_sample(menu_music);
    al_destroy_sample_instance(menu_music_inst);
    al_destroy_sample(playing_music);
    al_destroy_sample_instance(playing_music_inst);
    
    //delete[] vertexList;


    return 0;
}