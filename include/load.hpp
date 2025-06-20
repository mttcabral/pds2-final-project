#include "initializer_allegro.hpp"
#include <iostream>
#include <string>
using namespace std;

    // loading images and font
    ALLEGRO_BITMAP* menu_background = al_load_bitmap("assets/menu_background.png");
    ALLEGRO_BITMAP* play_button = al_load_bitmap("assets/menu_play_button.png");
    ALLEGRO_BITMAP* quit_button = al_load_bitmap("assets/menu_quit_button.png");
    ALLEGRO_BITMAP* hover_play = al_load_bitmap("assets/menu_hover_play_button.png");
    ALLEGRO_BITMAP* hover_quit = al_load_bitmap("assets/menu__hover_quit_button.png");
    ALLEGRO_FONT* menu_font = al_load_ttf_font("assets/PressStart2P-Regular.ttf", 72, 0);

    bool load_check(){
    if (!menu_background) std::cerr << "Erro: imagem menu_background não foi carregada!\n";
    if ( !play_button )     std::cerr << "Erro: imagem play_button não foi carregada!\n";
    if(!hover_play) std::cerr << "Erro: imagem hover_play não foi carregada \n";
    if (!quit_button)     std::cerr << "Erro: imagem quit_button não foi carregada!\n";
    if(!hover_quit) std::cerr << "Erro: imagem hover_quit não foi carregada\n";
    if(!menu_font) std::cerr << "Erro: fonte menu_font não foi carregada \n";


    // seeing if everything is alright
    if(!menu_background || !play_button || !quit_button || !menu_font || !hover_quit || !hover_play){
        return 1;
    }
    }
