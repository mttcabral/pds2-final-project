#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

/**
 * @brief Verifica se o mouse está sobre um bitmap na tela.
 *
 * @param event Evento do Allegro contendo informações do mouse.
 * @param any Ponteiro para o bitmap a ser verificado.
 * @param xcord Coordenada X do canto superior esquerdo do bitmap.
 * @param ycord Coordenada Y do canto superior esquerdo do bitmap.
 * @return true se o mouse está sobre o bitmap.
 * @return false caso contrário.
 */
bool hover_bool(ALLEGRO_EVENT event, ALLEGRO_BITMAP *any, int xcord, int ycord)
{
    int mousex = -1, mousey = -1;
    mousex = event.mouse.x;
    mousey = event.mouse.y;

    int any_w = al_get_bitmap_width(any);
    int any_h = al_get_bitmap_height(any);

    return (mousex >= xcord && mousex <= xcord + any_w && mousey >= ycord && mousey <= ycord + any_h);
}