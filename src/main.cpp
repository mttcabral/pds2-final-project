#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"
#include "initializer_allegro.hpp"
#include "game_object_handler.hpp"
#include "cooldown.hpp"
#include "animation.hpp"
#include "passive.hpp" 
#include "sound.hpp"
#include "leaderboard.hpp"
#include "table.hpp"
#include "interface.hpp"
#include <iostream>
#include <string>
#include "register.hpp"


using namespace std;

enum GameState {MENU, TRANSITION, PLAYING, LEADERBOARD, DEATH, QUIT, CHECKIN}; // Use for in game logic

// Game constants:
// const float FPS = 30;                                      // Frames per second (in cooldown.hpp)
// const float ANIM_FPS = 12;                                 // Frames per second for animation
const int SCREEN_W = 800;                                     // Screen width in pixels
const int SCREEN_H = 600;                                     // Screen height in pixels
const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);   // Background color (black)

int main(){

    // Basic Allegro pointers:
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *eventQueue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    ALLEGRO_TIMER *animation_timer = nullptr;
    
    // Initializations:

    //V-Sync:
    //tries to solve frame-skipping bug, still not solved !!!
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

    if(!initialize_allegro()) return 1;

    if(!initialize_event_queue(eventQueue)) return 1;

    if(!initialize_display_and_timer(display,SCREEN_W,SCREEN_H,timer,FPS)) return 1;
    
    if(!al_is_mouse_installed()) return 1;
    //if(!initialize_display(display,SCREEN_W,SCREEN_H)) return 1;

    if(!initialize_timer(timer,FPS)) return 1;
    if(!initialize_timer(animation_timer,ANIM_FPS)) return 1;

    // Register event sources for the event queue
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_timer_event_source(animation_timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    // Start the timer to control game speed
    al_start_timer(timer);
    al_start_timer(animation_timer);


    // Start the sample queue
    al_reserve_samples(10);
    
    //Redraw condition, so that the game is rendered separately from other events in queue
    bool redraw = false;

    TransitionScreen curtain;

    // loading images and font
    ALLEGRO_BITMAP* menu_background = al_load_bitmap("assets/menu_background.png");
    ALLEGRO_BITMAP* play_button = al_load_bitmap("assets/menu_play_button.png");
    ALLEGRO_BITMAP* quit_button = al_load_bitmap("assets/menu_quit_button.png");
    ALLEGRO_BITMAP* hover_play = al_load_bitmap("assets/menu_hover_play_button.png");
    ALLEGRO_BITMAP* hover_quit = al_load_bitmap("assets/menu__hover_quit_button.png");
    ALLEGRO_BITMAP* leaderboard_button = al_load_bitmap("assets/menu_leaderboard_button.png");
    ALLEGRO_BITMAP* hover_leaderboard = al_load_bitmap("assets/menu_hover_leaderboard_button.png");
    ALLEGRO_BITMAP* menu_image = al_load_bitmap("assets/title_image.png");
    ALLEGRO_BITMAP* back_button = al_load_bitmap("assets/back_button.png");
    ALLEGRO_BITMAP* hover_back = al_load_bitmap("assets/menu_hover_back_button.png");
    ALLEGRO_BITMAP* leaderboard_background = al_load_bitmap("assets/leaderboard_background.jpeg");
    ALLEGRO_BITMAP* home_button = al_load_bitmap("assets/home_button.png");
    ALLEGRO_BITMAP* hover_home = al_load_bitmap("assets/home_hover_button.png");
    ALLEGRO_BITMAP* retry_button = al_load_bitmap("assets/retry_button.png");
    ALLEGRO_BITMAP* hover_retry = al_load_bitmap("assets/retry_hover_button.png");
    ALLEGRO_FONT* textFont = al_load_font("assets/PressStart2P-Regular.ttf", 12, 0);

    // loading music (.wav please)
    ALLEGRO_SAMPLE* menu_music = al_load_sample("assets/DDDmario.wav");
    if(!menu_music) std::cerr << "Erro: música menu_music não foi carregada\n";
    ALLEGRO_SAMPLE* playing_music = al_load_sample("assets/Escape_Persona5.wav");
    if(!playing_music) std::cerr << "Erro: música playing_music não foi carregada\n";
    ALLEGRO_SAMPLE* leaderboard_music = al_load_sample("assets/leaderboard_music.wav");
    if(!leaderboard_music) std::cerr << "Erro: música da leaderboard não carregada\n";
    if (!textFont) std::cerr << "Erro: fonte textFont não foi carregada\n";
    

    //treating music
    ALLEGRO_SAMPLE_INSTANCE* menu_music_inst  = al_create_sample_instance(menu_music);
    ALLEGRO_SAMPLE_INSTANCE* playing_music_inst = al_create_sample_instance(playing_music);
    ALLEGRO_SAMPLE_INSTANCE* leaderboard_music_inst = al_create_sample_instance(leaderboard_music);
    // menu music

    startmusic(menu_music_inst, 0.5);
    // playing music
    startmusic(playing_music_inst, 0.1);
    startmusic(leaderboard_music_inst, 0.8);



    if (!menu_background) std::cerr << "Erro: imagem menu_background não foi carregada!\n";
    if (!play_button)     std::cerr << "Erro: imagem play_button não foi carregada!\n";
    if(!hover_play) std::cerr << "Erro: imagem hover_play não foi carregada \n";
    if (!quit_button)     std::cerr << "Erro: imagem quit_button não foi carregada!\n";
    if(!hover_quit) std::cerr << "Erro: imagem hover_quit não foi carregada\n";
    if(!back_button) std::cerr << "Erro: imagem back_button não foi carregada\n";
    if(!hover_back) std::cerr << "Erro: imagem hover_back não foi carregada\n";
    

    // seeing if everything is alright
    if(!menu_background || !play_button || !quit_button){
        return 1;
    }
    
 
    //coordinates of play, quit and leaderboard in MENU
    int xplay = 150, yplay = 400;
    int xquit = 490, yquit = 400;
    int xleader = 320, yleader = 400;
    int xhome = 150, yhome = 400;
    int xretry = 320, yretry = 400;

    //coordinates of back in LEADERBOARD
    int xback = 20, yback = 450;

    string path = "assets/base.csv";
    RectangleT plan(PointT(430, 312), 440, 420);
    LeaderBoard gameLeaderBoard(path, plan);

    gameLeaderBoard.setFirstRowTextColor(Color(255, 215, 0));
    gameLeaderBoard.setSecondRowTextColor(Color(192, 192, 192));
    gameLeaderBoard.setThirdRowTextColor(Color(205, 127, 50));
    gameLeaderBoard.setOthersRowsTextColor(Color(255, 255, 255));

    
    //testing sub bitmaps
    //TriggerSpritesheet sheetTest("assets/kirby.png",8,26,0);
    
    //testing background
    //the timing is not perfet at all, fix this later
    BackgroundHandler bgLayer3("assets/bg/sea.png",900,600,-1,SCREEN_W, SCREEN_H);
    BackgroundHandler bgLayer2("assets/bg/clouds.png",900,600,-4,SCREEN_W, SCREEN_H);
    BackgroundHandler bgLayer1("assets/bg/rocks.png",2700,600,-10,SCREEN_W, SCREEN_H);

    //testing cooldown
    Cooldown jumpCD(0);

    //Menu condition
    GameState state = MENU;
    GameState next = MENU;
    bool gameActive = true;

    bool Hplay = false, Hquit = false, Hleader = false, Hback = false, Hretry = false, Hmenu = false; //variables that detect if the hover effect is playing
    

    while(gameActive){
        if(state == MENU){
            al_play_sample_instance(menu_music_inst);
            al_stop_sample_instance(playing_music_inst);
            al_stop_sample_instance(leaderboard_music_inst);
        }   

        while(state == MENU){
            ALLEGRO_EVENT event;

            al_wait_for_event(eventQueue, &event);

            if(event.type == ALLEGRO_EVENT_TIMER){
                curtain.updateStage();
                curtain.updateSpeed();
                curtain.updatePosition();
                redraw = true;
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
               Hplay = hover_bool(event, play_button, xplay, yplay);
               Hquit = hover_bool(event, quit_button, xquit, yquit);
               Hleader = hover_bool(event,leaderboard_button, xleader, yleader);
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                if(Hplay) state = PLAYING;
                if(Hquit) {
                    state = QUIT;
                    gameActive = false;
                    } 
                if(Hleader) {
                    next = LEADERBOARD;
                    curtain.startTransition();
                    }
            }

            if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                state = QUIT;
                gameActive = false;
            }

            if(redraw && al_is_event_queue_empty(eventQueue)){
                al_clear_to_color(al_map_rgb(0,0,0)); 
                al_draw_bitmap(menu_background, 0, 0, 0);
                al_draw_bitmap(menu_image, 110, 30, 0);


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
                if(Hleader) {
                    al_draw_bitmap(hover_leaderboard, xleader, yleader, 0);
                } else {
                    al_draw_bitmap(leaderboard_button, xleader, yleader, 0);
                }
                
                al_flip_display();

                redraw = false;
            }
        }
        if(state == PLAYING){
            al_stop_sample_instance(menu_music_inst);
            al_stop_sample_instance(leaderboard_music_inst);
            al_play_sample_instance(playing_music_inst);
        }
        if(state == LEADERBOARD) {
            al_stop_sample_instance(menu_music_inst);
            al_stop_sample_instance(playing_music_inst);
            al_play_sample_instance(leaderboard_music_inst);
        }

        while(state == LEADERBOARD){
            //if (states == LE)
            ALLEGRO_EVENT event;

            al_wait_for_event(eventQueue, &event);

            if(event.type == ALLEGRO_EVENT_TIMER){
                redraw = true;
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
                Hback = hover_bool(event, back_button, xback, yback);
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if(Hback) state = MENU;
            }

            if(redraw && al_is_event_queue_empty(eventQueue)) {
                al_clear_to_color(al_map_rgb(0,0,0)); 
                al_draw_bitmap(leaderboard_background, 0, 0, 0);

                if(Hback) {
                    al_draw_bitmap(hover_back, xback, yback, 0);
                } else {
                    al_draw_bitmap(back_button, xback, yback, 0);
                }

                //toRegister.drawRegister(textFont);  // NEW METHOD AND CLASS TO DRAW THE REGISTER
                // al_flip_display();

                gameLeaderBoard.drawLeaderBoard(textFont);  // NEW METHOD TO DRAW THE LEADERBOARD
                al_flip_display();
            //
            }
            
            if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                gameActive = false;
                state = QUIT;
            }

            /* REGISTER LOGIC TO IMPLEMENT 
            if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
                cout << "KEY_CHAR" << endl;

                if (event.keyboard.unichar >= 32 && event.keyboard.unichar < 127){
                    cout << ">= 32 && < 127" << endl;
                    cout << "escrevendo" << endl;
                    bool wrote = toRegister.writeInBuffer((char)event.keyboard.unichar);
                    if(!wrote)
                        cout << "nao escreveu" << endl;
                }

                else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                    bool deleted = toRegister.deleteInBuffer();
                    if (!deleted) 
                        cout << "apagando" << endl;
                }
            }*/

        }   

        while (state == PLAYING) {
            Handler handler;
            int tempoSobrevivido = handler.gameOn(*timer, *animation_timer, *eventQueue, SCREEN_H, SCREEN_W); 
            if(tempoSobrevivido != 0){
                state = DEATH; // por enquanto só para permitir retry fácil
            }
            al_flip_display(); //updates the display with the new frame 
            redraw = false;
        }
        // death logic
        while (state == DEATH){
            ALLEGRO_EVENT event; 

            al_wait_for_event(eventQueue, &event);

            if(event.type == ALLEGRO_EVENT_TIMER){
                redraw = true;
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
                Hretry = hover_bool(event, retry_button, xretry, yretry);
                Hmenu = hover_bool(event, home_button, xhome, yhome);
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if(Hretry) state = PLAYING;
                if(Hmenu) state = MENU;
            }

                if(redraw && al_is_event_queue_empty(eventQueue)) {
                al_clear_to_color(al_map_rgb(0,0,0)); 

                if(Hretry) {
                    al_draw_bitmap(hover_retry, xretry, yretry, 0);
                } else {
                    al_draw_bitmap(retry_button, xretry, yretry, 0);
                }

                if(Hmenu) {
                    al_draw_bitmap(home_button, xhome, yhome, 0);
                } else {
                    al_draw_bitmap(hover_home, xhome, yhome, 0);
                }

                al_flip_display();
            //
            }
            
            if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                gameActive = false;
                state = QUIT;
            }

            
        }
    }
    al_destroy_bitmap(menu_image);
    al_destroy_bitmap(menu_background);
    al_destroy_bitmap(play_button);
    al_destroy_bitmap(quit_button);
    al_destroy_bitmap(hover_play);
    al_destroy_bitmap(hover_quit);
    al_destroy_display(display);

    al_destroy_event_queue(eventQueue);
    al_destroy_timer(timer);
    al_destroy_timer(animation_timer);
    al_destroy_sample(menu_music);
    al_destroy_sample_instance(menu_music_inst);
    al_destroy_sample(playing_music);
    al_destroy_sample_instance(playing_music_inst);
    al_destroy_font(textFont);
    



    return 0;
}