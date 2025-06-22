#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;


bool isHovering(ALLEGRO_EVENT event, ALLEGRO_BITMAP* any, int xcord, int ycord){
    int mousex = -1, mousey = -1;
    mousex = event.mouse.x;
    mousey = event.mouse.y;

    int any_w = al_get_bitmap_width(any);
    int any_h = al_get_bitmap_height(any);

    return (mousex>=xcord && mousex <= xcord + any_w && mousey>=ycord && mousey<= ycord + any_h);
}