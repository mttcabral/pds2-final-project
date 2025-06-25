#ifndef ALLINTERFACE_H
#define ALLINTERFACE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/**
 * @brief Inicia a reprodução de uma música em loop.
 *
 * @param any Ponteiro para a instância de sample do Allegro.
 * @param volume Volume da música (0.0 a 1.0).
 */
void startmusic(ALLEGRO_SAMPLE_INSTANCE *any, float volume)
{
    al_attach_sample_instance_to_mixer(any, al_get_default_mixer());
    al_set_sample_instance_playmode(any, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(any, volume);
}

#endif