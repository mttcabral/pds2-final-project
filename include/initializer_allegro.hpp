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
 * @brief Inicializa todos os módulos necessários da Allegro.
 *
 * @return true se todos os módulos foram inicializados com sucesso.
 * @return false se algum módulo falhar.
 */
bool initialize_allegro()
{
    // Initialize main allegro
    if (!al_init())
    {
        cout << "ERROR:" << "failed to initialize allegro" << endl;
        return false;
    }

    // Initialize Allegro primitives addon
    if (!al_init_primitives_addon())
    {
        cout << "ERROR:" << "failed to initialize allegro primitives" << endl;
        return false;
    }

    // Install keyboard input support
    if (!al_install_keyboard())
    {
        cout << "ERROR:" << "failed to initialize keyboard" << endl;
        return false;
    }
    if (!al_init_image_addon())
    {
        cout << "ERROR:" << "failed to initialize allegro image" << endl;
        return false;
    }

    // install mouse support
    if (!al_install_mouse())
    {
        return false;
    }

    if (!al_init_font_addon())
    {
        return false;
    }

    if (!al_init_ttf_addon())
    {
        return false;
    }

    if (!al_install_audio())
        return false;

    if (!al_init_acodec_addon())
        return false;

    return true;
}

/**
 * @brief Cria uma fila de eventos da Allegro.
 *
 * @param ev Referência para ponteiro de fila de eventos.
 * @return true se criada com sucesso.
 * @return false se falhar.
 */
bool initialize_event_queue(ALLEGRO_EVENT_QUEUE *&ev)
{
    ev = al_create_event_queue();
    if (!ev)
    {
        cout << "ERROR:" << "failed to create event_queue" << endl;
        return false;
    }
    else
        return true;
}

/**
 * @brief Inicializa a janela de exibição e o timer principal.
 *
 * @param display Referência para ponteiro de display.
 * @param w Largura da janela.
 * @param h Altura da janela.
 * @param t Referência para ponteiro de timer.
 * @param fps Taxa de quadros por segundo.
 * @return true se ambos foram inicializados com sucesso.
 * @return false se falhar.
 */
bool initialize_display_and_timer(ALLEGRO_DISPLAY *&display, int w, int h, ALLEGRO_TIMER *&t, float fps)
{
    display = al_create_display(w, h);
    if (!display)
    {
        cout << "ERROR:" << "failed to create display" << endl;
        return false;
    }
    else
    {
        t = al_create_timer(1.0 / fps);
        if (!t)
        {
            cout << "ERROR:" << "failed to initialize timer" << endl;
            al_destroy_display(display);
            return false;
        }
        else
            return true;
    }
}

/**
 * @brief Inicializa apenas a janela de exibição.
 *
 * @param display Referência para ponteiro de display.
 * @param w Largura da janela.
 * @param h Altura da janela.
 * @return true se inicializada com sucesso.
 * @return false se falhar.
 */
bool initialize_display(ALLEGRO_DISPLAY *&display, int w, int h)
{
    display = al_create_display(w, h);
    if (!display)
    {
        cout << "ERROR:" << "failed to create display" << endl;
        return false;
    }
    else
        return true;
}

/**
 * @brief Inicializa apenas o timer.
 *
 * @param t Referência para ponteiro de timer.
 * @param fps Taxa de quadros por segundo.
 * @return true se inicializado com sucesso.
 * @return false se falhar.
 */
bool initialize_timer(ALLEGRO_TIMER *&t, float fps)
{
    t = al_create_timer(1.0 / fps);
    if (!t)
    {
        cout << "ERROR:" << "failed to initialize timer" << endl;
        return false;
    }
    else
        return true;
}
