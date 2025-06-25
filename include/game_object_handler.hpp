#ifndef HANDLER_H
#define HANDLER_H

#include <list>
#include <memory>
#include <allegro5/allegro.h>
#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"

enum Ambient
{
    NONE,
    FLAPPY,
    EELS
};

class Handler
{
private:
    bool playing = false;
    Player guy;
    std::list<std::unique_ptr<Pipe>> obstacles;
    int time = 0;
    Ambient dynamic = NONE;
    float gameSpeed = 1;

public:
    /**
     * @brief Executa o loop principal do jogo.
     *
     * @param timer Timer principal do jogo.
     * @param animation_timer Timer para animações.
     * @param eventQueue Fila de eventos do Allegro.
     * @param SCREEN_H Altura da tela.
     * @param SCREEN_W Largura da tela.
     * @return int Pontuação final (tempo de sobrevivência).
     */
    int gameOn(ALLEGRO_TIMER &timer, ALLEGRO_TIMER &animation_timer, ALLEGRO_EVENT_QUEUE &eventQueue, const int SCREEN_H, const int SCREEN_W);

    /**
     * @brief Adiciona um novo obstáculo ao jogo.
     *
     * @param image Bitmap do obstáculo tipo Pipe.
     * @param eelImage Spritesheet do obstáculo tipo Eel.
     */
    void addObstacle(ALLEGRO_BITMAP *image, Spritesheet *eelImage);

    /**
     * @brief Verifica se o jogador saiu dos limites da tela.
     *
     * @return true Se saiu dos limites.
     * @return false Caso contrário.
     */
    bool outOfBorders();

    /**
     * @brief Verifica colisões entre o jogador e os obstáculos.
     *
     * @return true Se houve colisão.
     * @return false Caso contrário.
     */
    bool checkCollisions();

    /**
     * @brief Desenha todos os objetos do jogo na tela.
     */
    void drawAll();

    /**
     * @brief Executa procedimentos de morte do jogador.
     */
    void death();

    /**
     * @brief Sorteia um número inteiro entre min e max.
     *
     * @param min Valor mínimo.
     * @param max Valor máximo.
     * @return int Número sorteado.
     */
    int sortBetween(int x, int y);

    /**
     * @brief Atualiza o ambiente do jogo, mudando dinâmicas e velocidade.
     */
    void updateAmbient();

    void drawObstacles();
};

#endif
