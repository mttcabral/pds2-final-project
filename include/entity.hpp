#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.hpp"
#include "hitbox.hpp"
#include "animation.hpp"
#include "cooldown.hpp"
#include <string>

/// @brief Gravidade base aplicada às entidades.
const float BASE_GRAVITY = 10;
/// @brief Movimento base no eixo X.
const float BASE_X_MOVEMENT = 20;
/// @brief Posição base no eixo X.
const float X_AXIS = 160;

/**
 * @brief Classe base para objetos do jogo que podem interagir (possuem hitbox).
 */
class Entity : public Drawable
{
protected:
    Hitbox *hb; ///< Ponteiro para a hitbox da entidade.
public:
    /**
     * @brief Construtor da entidade com posição e velocidade.
     * @param pos Posição inicial.
     * @param spd Velocidade inicial.
     */
    Entity(const Point &pos, const Point &spd);

    /**
     * @brief Construtor da entidade apenas com posição.
     * @param pos Posição inicial.
     */
    Entity(const Point &pos);

    /**
     * @brief Retorna a hitbox da entidade.
     * @return Ponteiro para a hitbox.
     */
    Hitbox *getHitbox();

    /**
     * @brief Destrutor virtual.
     */
    virtual ~Entity();
};

/// @brief Tamanho padrão do jogador.
const float PLAYER_SIZE = 20;

/**
 * @brief Estados possíveis do jogador.
 */
enum class PlayerState
{
    NONE,
    DEAD,
    IDLE,
    JUMPING
};

/**
 * @brief Classe que representa o jogador principal.
 */
class Player : public Entity
{
private:
    Spritesheet idleSprite;                ///< Spritesheet de animação parado.
    TriggerSpritesheet jumpSprite;         ///< Spritesheet de animação de pulo.
    PlayerState state = PlayerState::NONE; ///< Estado atual do jogador.
    Cooldown angleCD;                      ///< Cooldown para controle de ângulo.
    float angle;                           ///< Ângulo do jogador.
public:
    /**
     * @brief Construtor padrão do jogador.
     */
    Player();

    /**
     * @brief Atualiza a posição do jogador.
     * @return true se a posição foi atualizada.
     */
    bool updatePosition() override;

    /**
     * @brief Atualiza a velocidade do jogador.
     */
    void updateSpeed() override;

    /**
     * @brief Realiza o pulo do jogador.
     */
    void jump();

    /**
     * @brief Desenha o jogador na tela.
     */
    void draw() override;

    // bool loadSprite(const char* dir);

    /**
     * @brief Atualiza o estado do jogador.
     */
    void updatePlayerState();

    /**
     * @brief Atualiza a animação do jogador.
     */
    void updateAnimation();

    /**
     * @brief Define o estado do jogador.
     * @param s Novo estado.
     */
    void setPlayerState(PlayerState s);

    /**
     * @brief Destrutor do jogador.
     */
    ~Player();
};

/// @brief Velocidade padrão do obstáculo Pipe no eixo X.
const float PIPE_X_SPEED = -10;

/**
 * @brief Classe básica para obstáculos do tipo Pipe.
 */
class Pipe : public Entity
{
private:
    ALLEGRO_BITMAP *pipeSprite = nullptr; ///< Bitmap do obstáculo.
    bool isInverted;                      ///< Indica se o obstáculo está invertido.
public:
    static float screenSpeed; ///< Velocidade global dos obstáculos.
    /**
     * @brief Atualiza a velocidade global dos obstáculos.
     * @param s Nova velocidade.
     */
    static void updateScreenSpeed(float s);

    /**
     * @brief Construtor do Pipe.
     * @param pos Posição inicial.
     * @param w Largura.
     * @param h Altura.
     * @param image Bitmap do obstáculo.
     * @param inv Indica se está invertido.
     */
    Pipe(const Point &pos, float w, float h, ALLEGRO_BITMAP *image = nullptr, bool inv = false);

    /**
     * @brief Atualiza a posição do obstáculo.
     * @return true se a posição foi atualizada.
     */
    bool updatePosition() override;

    /**
     * @brief Atualiza a velocidade do obstáculo.
     */
    void updateSpeed() override;

    /**
     * @brief Carrega o sprite do obstáculo.
     * @return true se carregado com sucesso.
     */
    bool loadSprite();

    /**
     * @brief Desenha o obstáculo na tela.
     */
    void draw() override;
};

/// @brief Largura padrão da enguia.
const float EEL_W = 366;
/// @brief Altura padrão da enguia.
const float EEL_H = 100;

/**
 * @brief Classe para obstáculos do tipo Eel (enguia).
 */
class Eel : public Pipe
{
private:
    Spritesheet *sprite; ///< Spritesheet da enguia.
public:
    /**
     * @brief Construtor da Eel.
     * @param pos Posição inicial.
     * @param image Spritesheet da enguia.
     */
    Eel(const Point &pos, Spritesheet *image);

    /**
     * @brief Rotaciona a enguia.
     */
    void rotate();

    /**
     * @brief Atualiza a posição da enguia.
     * @return true se a posição foi atualizada.
     */
    bool updatePosition() override;

    /**
     * @brief Desenha a enguia na tela.
     */
    void draw() override;
    //~Eel();
};

#endif