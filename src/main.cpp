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
enum RegisterState {NAME, NICKNAME, SAVE};

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
    bool mousenow = false;
    bool mousebefore = false;

    TransitionScreen curtain;

    // loading images and font
    ALLEGRO_BITMAP* menu_background = al_load_bitmap("assets/menu/menu_background.png"); 
    ALLEGRO_BITMAP* play_button = al_load_bitmap("assets/menu/menu_play_button.png");
    ALLEGRO_BITMAP* quit_button = al_load_bitmap("assets/menu/menu_quit_button.png");
    ALLEGRO_BITMAP* hover_play = al_load_bitmap("assets/menu/menu_hover_play_button.png");
    ALLEGRO_BITMAP* hover_quit = al_load_bitmap("assets/menu/menu__hover_quit_button.png");
    ALLEGRO_BITMAP* leaderboard_button = al_load_bitmap("assets/menu/menu_leaderboard_button.png");
    ALLEGRO_BITMAP* hover_leaderboard = al_load_bitmap("assets/menu/menu_hover_leaderboard_button.png");
    ALLEGRO_BITMAP* menu_image = al_load_bitmap("assets/menu/title_image.png");
    ALLEGRO_BITMAP* back_button = al_load_bitmap("assets/menu/back_button.png");
    ALLEGRO_BITMAP* hover_back = al_load_bitmap("assets/menu/menu_hover_back_button.png");
    ALLEGRO_BITMAP* leaderboard_background = al_load_bitmap("assets/menu/leaderboard_background.jpeg");
    ALLEGRO_BITMAP* home_button = al_load_bitmap("assets/menu/home_button.png");
    ALLEGRO_BITMAP* hover_home = al_load_bitmap("assets/menu/home__hover_button.png");
    ALLEGRO_BITMAP* retry_button = al_load_bitmap("assets/menu/retry_button.png");
    ALLEGRO_BITMAP* hover_retry = al_load_bitmap("assets/menu/retry_hover_button.png");
    ALLEGRO_BITMAP* game_over_background = al_load_bitmap("assets/menu/game_over_background.png");
    ALLEGRO_BITMAP* register_button = al_load_bitmap("assets/menu/register_button.png");
    ALLEGRO_BITMAP* hover_register = al_load_bitmap("assets/menu/register_hover_button.png");
    ALLEGRO_BITMAP* no_button = al_load_bitmap("assets/menu/no_button.png");
    ALLEGRO_BITMAP* hover_no = al_load_bitmap("assets/menu/no_hover_button.png");
    ALLEGRO_BITMAP* yes_button = al_load_bitmap("assets/menu/yes_button.png");
    ALLEGRO_BITMAP* hover_yes = al_load_bitmap("assets/menu/yes_hover_button.png");
    ALLEGRO_BITMAP* register_background = al_load_bitmap("assets/menu/register_background.png");
    ALLEGRO_FONT* textFont = al_load_font("assets/PressStart2P-Regular.ttf", 12, 0);

    // loading music (.wav please) 
    ALLEGRO_SAMPLE* menu_music = al_load_sample("assets/music/DDDmario.wav");
    if(!menu_music) std::cerr << "Erro: música menu_music não foi carregada\n";
    ALLEGRO_SAMPLE* playing_music = al_load_sample("assets/music/Escape_Persona5.wav");
    if(!playing_music) std::cerr << "Erro: música playing_music não foi carregada\n";
    ALLEGRO_SAMPLE* leaderboard_music = al_load_sample("assets/music/leaderboard_music.wav");
    if(!leaderboard_music) std::cerr << "Erro: música da leaderboard não carregada\n";
    if (!textFont) std::cerr << "Erro: fonte textFont não foi carregada\n";

    ALLEGRO_SAMPLE* error_soundeffect = al_load_sample("assets/music/soundeffect/error_soundeffect.wav");
    ALLEGRO_SAMPLE* gaming_start = al_load_sample("assets/music/soundeffect/gaming_start.ogg");
    ALLEGRO_SAMPLE* hover_soundeffect = al_load_sample("assets/music/soundeffect/hover_soundeffect.wav");
    ALLEGRO_SAMPLE* register_soundeffect = al_load_sample("assets/music/soundeffect/register_soundeffect.wav");
    ALLEGRO_SAMPLE* select_soundeffect = al_load_sample("assets/music/soundeffect/select_soundeffect.wav");
    ALLEGRO_SAMPLE* death_music = al_load_sample("assets/music/death_soundtrack.wav");
    

    //treating music
    ALLEGRO_SAMPLE_INSTANCE* menu_music_inst  = al_create_sample_instance(menu_music);
    ALLEGRO_SAMPLE_INSTANCE* playing_music_inst = al_create_sample_instance(playing_music);
    ALLEGRO_SAMPLE_INSTANCE* leaderboard_music_inst = al_create_sample_instance(leaderboard_music);
    ALLEGRO_SAMPLE_INSTANCE* death_music_inst = al_create_sample_instance(death_music);
    // menu music

    startmusic(menu_music_inst, 0.5);
    // playing music
    startmusic(playing_music_inst, 0.5);
    startmusic(leaderboard_music_inst, 0.8);
    startmusic(death_music_inst, 0.5);



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

    int xhome = 600, yhome = 450;
    int xretry = 100, yretry = 450;
    int xreg = 350, yreg = 450;

    //coordinates of back in LEADERBOARD
    int xback = 20, yback = 450;

    string path = "assets/base.csv";
    RectangleT plan(PointT(430, 312), 440, 420);
    LeaderBoard gameLeaderBoard(path, plan);

    gameLeaderBoard.setFirstRowTextColor(Color(255, 215, 0));
    gameLeaderBoard.setSecondRowTextColor(Color(192, 192, 192));
    gameLeaderBoard.setThirdRowTextColor(Color(205, 127, 50));
    gameLeaderBoard.setOthersRowsTextColor(Color(255, 255, 255));

    Register nameRegister("PLEASE, ENTER YOUR NAME:", 20, RectangleT(PointT(400, 300), 200, 150));
    nameRegister.setTittleTextColor(Color(0, 0, 255));
    nameRegister.setMessageTextColor(Color(255, 0, 0));
    nameRegister.setBufferTextColor(Color(0, 0, 0));

    Register nicknameRegister("ENTER YOUR NICKNAME:", 20, RectangleT(PointT(400, 300), 200, 150));
    nicknameRegister.setTittleTextColor(Color(0, 255, 0));
    nicknameRegister.setMessageTextColor(Color(255, 0, 0));
    nicknameRegister.setBufferTextColor(Color(0, 0, 0));
    
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

    // Register condition
    RegisterState operation = NAME;
    string tryName = "";
    string tryNickname = "";
    Profile tryProfile = Profile();
    bool yetRegistered = false;
    int pontuation = 0;

    bool Hplay = false, Hquit = false, Hleader = false, Hback = false, Hretry = false, Hmenu = false, Hregister = false; //variables that detect if the hover effect is playing
    

    while(gameActive){
        if(state == MENU){
            al_play_sample_instance(menu_music_inst);
            al_stop_sample_instance(playing_music_inst);
            al_stop_sample_instance(leaderboard_music_inst);
            al_stop_sample_instance(death_music_inst);
        }   

        while(state == MENU){
            ALLEGRO_EVENT event;

            al_wait_for_event(eventQueue, &event);

            if(event.type == ALLEGRO_EVENT_TIMER){
                redraw = true;
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
               Hplay = hover_bool(event, play_button, xplay, yplay);
               Hquit = hover_bool(event, quit_button, xquit, yquit);
               Hleader = hover_bool(event,leaderboard_button, xleader, yleader);
               
            }
            mousebefore = mousenow;
            mousenow = (Hplay || Hquit || Hleader);
            if(mousenow && !mousebefore){
                al_play_sample(hover_soundeffect, 0.4, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }


            if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                if(Hplay) {
                    al_play_sample(gaming_start, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);;
                    state = PLAYING;
                    }
                if(Hquit) {
                    state = QUIT;
                    gameActive = false;
                    } 
                if(Hleader) {
                    al_play_sample(select_soundeffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);;
                   state = LEADERBOARD;
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
            al_stop_sample_instance(death_music_inst);
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

                gameLeaderBoard.drawLeaderBoard(textFont);  // NEW METHOD TO DRAW THE LEADERBOARD
                al_flip_display();
            //
            }
            
            if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                gameActive = false;
                state = QUIT;
            }


        }   

        while (state == PLAYING) {
            Handler handler;
            int tempoSobrevivido = handler.gameOn(*timer, *animation_timer, *eventQueue, SCREEN_H, SCREEN_W); 
            if(tempoSobrevivido == -1){
                state = DEATH; // por enquanto só para permitir retry fácil
                al_stop_sample_instance(playing_music_inst);
                al_play_sample_instance(death_music_inst);
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
                Hregister = hover_bool(event, register_button, xreg, yreg);

            }

            mousebefore = mousenow;
            mousenow = (Hretry || Hmenu || Hregister);
            if(mousenow && !mousebefore){
                al_play_sample(hover_soundeffect, 0.4, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if(Hretry) {
                    al_play_sample(select_soundeffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);;
                    state = PLAYING;
                    }
                if(Hmenu) {
                    al_play_sample(select_soundeffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    state = MENU;
                    }
                if(Hregister) {
                    al_play_sample(select_soundeffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    state = CHECKIN;
                }
            }

            if(redraw && al_is_event_queue_empty(eventQueue)) {
                al_draw_bitmap(game_over_background, 0, 0, 0);

                    if(Hretry) {
                    al_draw_bitmap(hover_retry, xretry, yretry, 0);
                    } else {
                    al_draw_bitmap(retry_button, xretry, yretry, 0);
                    }

                    if(Hmenu) {
                    al_draw_bitmap(hover_home, xhome, yhome, 0);
                    } else {
                    al_draw_bitmap(home_button, xhome, yhome, 0);
                    }
                    if(Hregister) {
                        al_draw_bitmap(hover_register, xreg, yreg, 0);
                    } else {
                        al_draw_bitmap(register_button, xreg, yreg, 0);
                    }
                    

                    al_flip_display();
            //
            }
            
            if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                gameActive = false;
                state = QUIT;
            }

            
        }

        while (state == CHECKIN){
            ALLEGRO_EVENT event; 

            al_wait_for_event(eventQueue, &event);

            if(event.type == ALLEGRO_EVENT_TIMER){
                redraw = true;
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
                Hretry = hover_bool(event, yes_button, xretry, yretry);
                Hmenu = hover_bool(event, no_button, xhome, yhome);
            }

            if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if(Hretry) {} // SIM QUERO FAZER NOVO REGISTRO
                if(Hmenu) {} // NÃO NÃO QUERO FAZER NOVO REGISTRO
            }

            if(redraw && al_is_event_queue_empty(eventQueue)) {
                al_draw_bitmap(register_background, 0, 0, 0);

                    if(Hretry) {
                    al_draw_bitmap(hover_yes, xretry, yretry, 0);
                    } else {
                    al_draw_bitmap(yes_button, xretry, yretry, 0);
                    }

                    if(Hmenu) {
                    al_draw_bitmap(hover_no, xhome, yhome, 0);
                    } else {
                    al_draw_bitmap(no_button, xhome, yhome, 0);
                    }
                    
                    if (operation == NAME){
                        nameRegister.drawRegister(textFont);  // NEW METHOD AND CLASS TO DRAW THE REGISTER
                    }
                    else if (operation == NICKNAME) {
                        nicknameRegister.drawRegister(textFont);
                    }
                    al_flip_display();
            }

            if(operation == NAME){
                tryName = "";
                if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
                    if (event.keyboard.unichar >= 32 && event.keyboard.unichar < 127)
                        nameRegister.writeInBuffer((char)event.keyboard.unichar);

                    else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
                        nameRegister.deleteInBuffer();
                
                    else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                        string warning = "";
                        tryName = nameRegister.getBufferContent();
                        bool nameRegistered = checkName(tryName, warning);
                        nameRegister.setMessageContent(warning);
                        nameRegister.cleanBuffer();

                        if (nameRegistered)
                            operation = NICKNAME;
                    }
                }
            }

            if(operation == NICKNAME){
                tryNickname = "";
                if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
                    if (event.keyboard.unichar >= 32 && event.keyboard.unichar < 127)
                        nicknameRegister.writeInBuffer((char)event.keyboard.unichar);

                    else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
                        nicknameRegister.deleteInBuffer();
                
                    else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                        string warning = "";
                        tryNickname = nicknameRegister.getBufferContent();
                        bool nicknameRegistered = checkNickname(tryNickname, warning);
                        nicknameRegister.setMessageContent(warning);
                        nicknameRegister.cleanBuffer();

                        if (nicknameRegistered)
                            operation = SAVE;
                    }
                }
            }

            if(operation == SAVE){
                bool profileRegistered = gameLeaderBoard.addNewProfile(Profile(tryName, tryNickname, pontuation, 1)); // 800 eh pra teste. Passar o valor da distancia da partida
                operation = NAME;
                if (profileRegistered) {
                    state = MENU;
                    gameLeaderBoard.updateLeaderBoard();
                    gameLeaderBoard.save(path);
                }
                else {
                    nicknameRegister.setMessageContent("Nickname already in use. Try another one.");
                    operation = NICKNAME;
                }
                
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