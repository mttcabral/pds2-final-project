#ifndef HITBOX_H
#define HITBOX_H

#include "game_object.hpp"

/**
 * @brief Classe base para hitboxes de objetos do jogo.
 *
 * Utilizada para determinar o espaço ocupado no jogo e interagir com outros objetos desenháveis.
 */
class Hitbox : public GameObject
{
private:
    Drawable *target; ///< Objeto associado à hitbox (sempre existe uma relação 1:1).
public:
    /**
     * @brief Construtor da hitbox.
     * @param center Centro da hitbox.
     */
    Hitbox(const Point &center);

    /**
     * @brief Atualiza a posição da hitbox.
     * @return true se a posição foi atualizada.
     */
    bool updatePosition() override;

    /**
     * @brief Define o objeto alvo associado à hitbox.
     * @param target Ponteiro para o objeto Drawable.
     */
    void setTarget(Drawable *target);

    /**
     * @brief Retorna o polígono da hitbox.
     * @return Polígono da hitbox.
     */
    virtual Polygon getPolygon() = 0;

    /**
     * @brief Retorna o ângulo da hitbox.
     * @return Ângulo em radianos.
     */
    virtual float getAngle() = 0;

    /**
     * @brief Rotaciona a hitbox.
     * @param radians Ângulo em radianos.
     */
    virtual void rotateHitbox(float radians) = 0;

    /**
     * @brief Destrutor virtual da hitbox.
     */
    virtual ~Hitbox();
};

/**
 * @brief Hitbox retangular, usada para representar retângulos com largura e altura variáveis.
 */
class RectangleHitbox : public Hitbox
{
private:
    float width;         ///< Largura do retângulo.
    float height;        ///< Altura do retângulo.
    Rectangle rectangle; ///< Objeto retângulo associado.
public:
    /**
     * @brief Construtor da hitbox retangular.
     * @param center Centro da hitbox.
     * @param w Largura.
     * @param h Altura.
     */
    RectangleHitbox(const Point &center, float w, float h);

    // bool checkColision() override;

    /**
     * @brief Retorna a largura da hitbox.
     * @return Largura.
     */
    float getWidth();

    /**
     * @brief Retorna a altura da hitbox.
     * @return Altura.
     */
    float getHeight();

    /**
     * @brief Retorna o polígono da hitbox.
     * @return Polígono.
     */
    Polygon getPolygon() override;

    /**
     * @brief Retorna o ângulo da hitbox.
     * @return Ângulo em radianos.
     */
    float getAngle() override;

    /**
     * @brief Atualiza a posição da hitbox.
     * @return true se a posição foi atualizada.
     */
    bool updatePosition() override;

    /**
     * @brief Rotaciona a hitbox.
     * @param radians Ângulo em radianos.
     */
    void rotateHitbox(float radians) override;

    /**
     * @brief Retorna os vértices do retângulo.
     * @return Ponteiro para array de vértices.
     */
    float *getVertices();
};

/**
 * @brief Hitbox com formato de polígono regular.
 */
class PolygonHitbox : public Hitbox
{
private:
    int sides;              ///< Número de lados do polígono.
    RegularPolygon polygon; ///< Polígono regular associado.
public:
    /**
     * @brief Construtor da hitbox poligonal.
     * @param center Centro da hitbox.
     * @param n Número de lados.
     * @param EdgeLength Tamanho da aresta.
     */
    PolygonHitbox(const Point &center, int n, float EdgeLength);

    /**
     * @brief Retorna o número de lados do polígono.
     * @return Número de lados.
     */
    int getSideCount();

    /**
     * @brief Retorna o tamanho da aresta.
     * @return Tamanho da aresta.
     */
    float getEdgeLength();

    /**
     * @brief Retorna o polígono da hitbox.
     * @return Polígono.
     */
    Polygon getPolygon() override;

    /**
     * @brief Retorna o ângulo da hitbox.
     * @return Ângulo em radianos.
     */
    float getAngle() override;

    /**
     * @brief Atualiza a posição da hitbox.
     * @return true se a posição foi atualizada.
     */
    bool updatePosition() override;

    /**
     * @brief Rotaciona a hitbox.
     * @param radians Ângulo em radianos.
     */
    void rotateHitbox(float radians) override;

    /**
     * @brief Retorna os vértices do polígono.
     * @return Ponteiro para array de vértices.
     */
    float *getVertices();
};

#endif