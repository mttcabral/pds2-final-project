#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "polygon.hpp"

/**
 * @brief Classe base para todos os objetos do jogo.
 */
class GameObject
{
private:
    Point pos; ///< Vetor de posição do objeto na tela.

protected:
    /**
     * @brief Construtor protegido com posição.
     * @param position Posição inicial do objeto.
     */
    GameObject(const Point &position);

    /**
     * @brief Construtor protegido com coordenadas.
     * @param pX Coordenada X.
     * @param pY Coordenada Y.
     */
    GameObject(float pX, float pY);

    /**
     * @brief Define a coordenada X do objeto.
     * @param x Nova coordenada X.
     */
    void setPosX(float x);

    /**
     * @brief Define a coordenada Y do objeto.
     * @param y Nova coordenada Y.
     */
    void setPosY(float y);

    /**
     * @brief Define a posição do objeto.
     * @param p Nova posição.
     */
    void setPos(const Point &p);

public:
    /**
     * @brief Retorna a posição do objeto.
     * @return Posição atual.
     */
    Point getPos();

    /**
     * @brief Retorna a coordenada X do objeto.
     * @return Coordenada X.
     */
    float getPosX();

    /**
     * @brief Retorna a coordenada Y do objeto.
     * @return Coordenada Y.
     */
    float getPosY();

    /**
     * @brief Atualiza a posição do objeto.
     * @return true se a posição foi atualizada.
     */
    virtual bool updatePosition() = 0;
};

/**
 * @brief Classe base para todos os objetos desenháveis e que podem se mover.
 */
class Drawable : public GameObject
{
private:
    Point speed; ///< Vetor de velocidade do objeto.
protected:
    /**
     * @brief Construtor protegido com posição e velocidade.
     * @param pos Posição inicial.
     * @param spd Velocidade inicial.
     */
    Drawable(const Point &pos, const Point &spd);

    /**
     * @brief Construtor protegido apenas com posição.
     * @param pos Posição inicial.
     */
    Drawable(const Point &pos);

    /**
     * @brief Define a velocidade no eixo X.
     * @param x Nova velocidade X.
     */
    void setSpeedX(float x);

    /**
     * @brief Define a velocidade no eixo Y.
     * @param y Nova velocidade Y.
     */
    void setSpeedY(float y);

    /**
     * @brief Define o vetor de velocidade.
     * @param pos Novo vetor de velocidade.
     */
    void setSpeed(const Point &pos);

public:
    /**
     * @brief Desenha o objeto na tela.
     */
    virtual void draw() = 0;

    /**
     * @brief Atualiza a velocidade do objeto.
     */
    virtual void updateSpeed() = 0;

    /**
     * @brief Adiciona um vetor à velocidade atual.
     * @param spd Vetor a ser adicionado.
     */
    void addSpeedVector(const Point &spd);

    /**
     * @brief Adiciona um valor à velocidade X.
     * @param x Valor a ser adicionado.
     */
    void addSpeedX(float x);

    /**
     * @brief Adiciona um valor à velocidade Y.
     * @param y Valor a ser adicionado.
     */
    void addSpeedY(float y);

    /**
     * @brief Retorna o vetor de velocidade.
     * @return Vetor de velocidade.
     */
    Point getSpeed();

    /**
     * @brief Retorna a velocidade no eixo X.
     * @return Velocidade X.
     */
    float getSpeedX();

    /**
     * @brief Retorna a velocidade no eixo Y.
     * @return Velocidade Y.
     */
    float getSpeedY();
};

#endif