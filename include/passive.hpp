#ifndef PASSIVE_H
#define PASSIVE_H

#include "game_object.hpp"
#include "cooldown.hpp"
#include <vector>

/**
 * @brief Classe que representa um plano de fundo do jogo.
 */
class Background : public Drawable
{
protected:
    ALLEGRO_BITMAP *image = nullptr; ///< Bitmap do plano de fundo.
    float width;                     ///< Largura do plano de fundo.
    float height;                    ///< Altura do plano de fundo.
public:
    /**
     * @brief Construtor do plano de fundo.
     * @param dir Caminho da imagem.
     * @param pos Posição inicial.
     * @param w Largura.
     * @param h Altura.
     * @param speedX Velocidade no eixo X.
     */
    Background(const char *dir, const Point &pos, float w, float h, float speedX);

    /**
     * @brief Destrutor virtual do plano de fundo.
     */
    virtual ~Background();

    /**
     * @brief Atualiza a velocidade do plano de fundo.
     */
    void updateSpeed() override;

    /**
     * @brief Atualiza a posição do plano de fundo.
     * @return true se a posição foi atualizada.
     */
    bool updatePosition() override;

    /**
     * @brief Desenha o plano de fundo na tela.
     */
    void draw() override;

    friend class BackgroundHandler;
};

/**
 * @brief Classe responsável por gerenciar múltiplos planos de fundo.
 */
class BackgroundHandler
{
private:
    std::vector<Background *> bgPair; ///< Vetor de ponteiros para planos de fundo.
    float screenWidth;                ///< Largura da tela.
    float screenHeight;               ///< Altura da tela.
    Point anchor;                     ///< Âncora de posicionamento.
public:
    /**
     * @brief Construtor do gerenciador de planos de fundo.
     * @param dir Caminho da imagem.
     * @param w Largura do plano de fundo.
     * @param h Altura do plano de fundo.
     * @param speedX Velocidade no eixo X.
     * @param screenW Largura da tela.
     * @param screenH Altura da tela.
     */
    BackgroundHandler(const char *dir, float w, float h,
                      float speedX, float screenW, float screenH);

    /**
     * @brief Destrutor do gerenciador de planos de fundo.
     */
    ~BackgroundHandler();

    /**
     * @brief Desenha todos os planos de fundo.
     */
    void drawBackground();

    /**
     * @brief Atualiza a posição dos planos de fundo.
     */
    void updateBackgroundPosition();
};

/**
 * @brief Enumeração dos estágios da tela de transição.
 */
enum class tStage
{
    NONE,
    FIRST_HALF,
    SECOND_HALF
};

/// @brief Âncora padrão da transição.
const Point T_ANCHOR(400, 950);
/// @brief Velocidade padrão da transição.
const float T_SPEED = 18;
/// @brief Tempo padrão da transição.
const float T_TIME = (750 / (T_SPEED * FPS));

/**
 * @brief Classe que representa a tela de transição do jogo.
 */
class TransitionScreen : public Background
{
private:
    Cooldown cd;                 ///< Cooldown da transição.
    tStage stage = tStage::NONE; ///< Estágio atual da transição.
public:
    /**
     * @brief Construtor da tela de transição.
     */
    TransitionScreen();

    /**
     * @brief Atualiza a velocidade da transição.
     */
    void updateSpeed() override;

    /**
     * @brief Atualiza a posição da transição.
     * @return true se a posição foi atualizada.
     */
    bool updatePosition() override;

    /**
     * @brief Desenha a tela de transição.
     */
    void draw() override;

    /**
     * @brief Atualiza o estágio da transição.
     */
    void updateStage();

    /**
     * @brief Inicia a transição.
     */
    void startTransition();

    /**
     * @brief Verifica se a transição está ativa.
     * @return true se ativa.
     */
    bool isActive();

    /**
     * @brief Retorna o estágio atual da transição.
     * @return Estágio da transição.
     */
    tStage getStage();
};

#endif