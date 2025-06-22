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


using namespace std;

enum GameState {MENU, TRANSITION, PLAYING, LEADERBOARD, DEATH, QUIT}; // Use for in game logic

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

    ALLEGRO_COLOR colisionIndicatorColor = al_map_rgb(20,140,20);

    // Basic player object for testing
    // BasicPlayer squareguy;
    Player guy;
    //guy.loadSprite("assets/guy.png");
    // Basic obstacle object for testing
    Pipe obstacle(Point(800,300),50,300);
    //Pipe obstacle(Point(200,600),128,128);
    obstacle.loadSprite("assets/long.png");

    //testing transition:
    TransitionScreen curtain;

    //curtain.startTransition();

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

    //coordinates of back in LEADERBOARD
    int xback = 20, yback = 450;

    string path = "assets/base.csv";
    RectangleT plan(PointT(400, 300), 600, 500);
    LeaderBoard gameLeaderBoard(path, plan);

    gameLeaderBoard.setTitleRowTextColor(Color(128, 0, 128));
    gameLeaderBoard.setFirstRowTextColor(Color(255, 215, 0));
    gameLeaderBoard.setSecondRowTextColor(Color(192, 192, 192));
    gameLeaderBoard.setThirdRowTextColor(Color(205, 127, 50));


    ALLEGRO_COLOR baseBackgroundColor = al_map_rgba_f(0.7,0.7,0.9,1);
    
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
    GameState nextState = MENU;
    bool gameActive = true;

    bool Hplay = false, Hquit = false, Hleader = false, Hback = false; //variables that detect if the hover effect is playing
    

    while(gameActive){
        if(state == MENU){
            al_play_sample_instance(menu_music_inst);
            al_stop_sample_instance(playing_music_inst);
            al_stop_sample_instance(leaderboard_music_inst);
        }   
        
        while(state == MENU){
            ALLEGRO_EVENT event;

            al_wait_for_event(eventQueue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_TIMER:
                    curtain.updateStage();
                    curtain.updateSpeed();
                    curtain.updatePosition();
                    redraw = true;
                    break;

                case ALLEGRO_EVENT_MOUSE_AXES: case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
                    Hplay = isHovering(event, play_button, xplay, yplay);
                    Hquit = isHovering(event, quit_button, xquit, yquit);
                    Hleader = isHovering(event,leaderboard_button, xleader, yleader);
                    break;

                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                    if(Hplay) state = PLAYING;
                    if(Hquit) {
                        state = QUIT;
                        gameActive = false;
                    } 
                    if(Hleader) {
                        nextState = LEADERBOARD;
                        curtain.startTransition();
                    }
                    break;

                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    state = QUIT;
                    gameActive = false;
                    break;

            }

            if (curtain.getStage() == tStage::SECOND_HALF) state = nextState;

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
                
                if (curtain.isActive()) curtain.draw();
                //al_draw_bitmap(curtain.getImage(),0,0,0);

                al_flip_display();

                redraw = false;
            }
        }


        if(state == PLAYING){
            al_stop_sample_instance(menu_music_inst);
            al_stop_sample_instance(leaderboard_music_inst);
            al_play_sample_instance(playing_music_inst);
        }else if(state == LEADERBOARD) {
            al_stop_sample_instance(menu_music_inst);
            al_stop_sample_instance(playing_music_inst);
            al_play_sample_instance(leaderboard_music_inst);
        }

        while(state == LEADERBOARD){
            ALLEGRO_EVENT event;

            al_wait_for_event(eventQueue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_TIMER:
                    curtain.updateStage();
                    curtain.updateSpeed();
                    curtain.updatePosition();
                    redraw = true;
                    break;

                case ALLEGRO_EVENT_MOUSE_AXES: case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
                    Hback = isHovering(event, back_button, xback, yback);
                    break;
                    
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                    if(Hback) {
                        nextState = MENU;
                        curtain.startTransition();
                    } 
                    break;
                
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    gameActive = false;
                    state = QUIT;
                    break;
                    
            }

            if (curtain.getStage() == tStage::SECOND_HALF) state = nextState;

            if(redraw && al_is_event_queue_empty(eventQueue)) {
                al_clear_to_color(al_map_rgb(255, 255, 255));

                if(Hback) {
                    al_draw_bitmap(hover_back, xback, yback, 0);
                } else {
                    al_draw_bitmap(back_button, xback, yback, 0);
                }

                for (Row line : gameLeaderBoard.table.row) {
                    Color tempTextColor = line.textColor;
                    ALLEGRO_COLOR aColor = al_map_rgb(tempTextColor.r, tempTextColor.g, tempTextColor.b);
                    for (int i = 0; i < NUMCOLUMNS; i++){
                        float subX = line.rowRectangle.subCenters[i].x;
                        float subY = line.rowRectangle.subCenters[i].y;
                        char const *aText = line.texts[i].c_str();
                        al_draw_text(textFont, aColor, subX, subY, ALLEGRO_ALIGN_CENTRE, aText);
                    }
                }

                if (curtain.isActive()) curtain.draw();

                al_flip_display();

                redraw = false;
            //
            }
        }   

        while (state == PLAYING) {
            
            ALLEGRO_EVENT event;

            al_wait_for_event(eventQueue, &event);

            switch (event.type) {
                case ALLEGRO_EVENT_TIMER:
                if (event.timer.source == timer) {
                    guy.updateSpeed();
                    guy.updatePosition(); 
                    guy.updatePlayerState();
                    obstacle.updateSpeed();
                    obstacle.updatePosition();
                    
                    bgLayer3.updateBackgroundPosition();
                    bgLayer2.updateBackgroundPosition();
                    bgLayer1.updateBackgroundPosition();

                    curtain.updateStage();
                    curtain.updateSpeed();
                    curtain.updatePosition();


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
                    
                } else if (event.timer.source == animation_timer) {
                    guy.updateAnimation();
                }

                break;
                case ALLEGRO_EVENT_KEY_DOWN:
                    switch (event.keyboard.keycode){
                        case ALLEGRO_KEY_SPACE: case ALLEGRO_KEY_UP:
                            if (jumpCD.isCooldownUp()) {
                                guy.jump();
                                jumpCD.restartCooldown();
                                //sheetTest.resetAnimation();
                            }
                            //cout << "Jump\n";
                            break;
                        }
                break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    gameActive = false;
                    state = QUIT;
                break;
            }

            //redraw frame
            if (redraw && al_is_event_queue_empty(eventQueue)) {
                //refresh display
                al_clear_to_color(baseBackgroundColor);

                //bg
                bgLayer3.drawBackground();
                bgLayer2.drawBackground();
                bgLayer1.drawBackground();

                //objects
                guy.draw();
                obstacle.draw();

                if (curtain.isActive()) curtain.draw();
                
                al_flip_display(); //updates the display with the new frame 

                redraw = false;
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