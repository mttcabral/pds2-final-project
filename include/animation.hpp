#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <iostream>

#include <allegro5/allegro.h>

using namespace std;

/// @brief FPS padrão das animações.
const float ANIM_FPS = 24;

/**
 * @brief Classe que representa uma spritesheet para animações.
 */
class Spritesheet
{
protected:
    ALLEGRO_BITMAP *sheet = nullptr;
    int frameCount, frameWidth, frameHeight, frameGap;
    int currentIndex = 0;
    vector<ALLEGRO_BITMAP *> frames;

public:
    /**
     * @brief Construtor da spritesheet.
     * @param dir Caminho do arquivo da spritesheet.
     * @param count Quantidade de frames.
     * @param frameW Largura de cada frame.
     * @param frameH Altura de cada frame.
     * @param gap Espaço entre frames.
     */
    Spritesheet(const char *dir, int count, int frameW, int frameH, int gap);

    /**
     * @brief Construtor alternativo da spritesheet.
     * @param dir Caminho do arquivo da spritesheet.
     * @param count Quantidade de frames.
     * @param frameW Largura de cada frame.
     * @param gap Espaço entre frames.
     */
    Spritesheet(const char *dir, int count, int frameW, int gap);

    // void loadBitmap(const char* dir);

    /**
     * @brief Retorna o bitmap da spritesheet.
     * @return ALLEGRO_BITMAP* Bitmap da spritesheet.
     */
    ALLEGRO_BITMAP *getSheet() const;

    /**
     * @brief Retorna a quantidade de frames.
     * @return int Número de frames.
     */
    int getFrameCount() const;

    /**
     * @brief Retorna a largura de cada frame.
     * @return int Largura do frame.
     */
    int getFrameWidth() const;

    /**
     * @brief Retorna a altura de cada frame.
     * @return int Altura do frame.
     */
    int getFrameHeight() const;

    /**
     * @brief Retorna o índice do frame atual.
     * @return int Índice do frame atual.
     */
    int getCurrentIndex() const;

    /**
     * @brief Retorna o frame na posição i.
     * @param i Índice do frame.
     * @return ALLEGRO_BITMAP* Frame selecionado.
     */
    ALLEGRO_BITMAP *getFrame(int i) const;

    /**
     * @brief Retorna o frame atual.
     * @return ALLEGRO_BITMAP* Frame atual.
     */
    ALLEGRO_BITMAP *getCurrentFrame() const;

    /**
     * @brief Reinicia a animação para o primeiro frame.
     */
    virtual void resetAnimation();

    /**
     * @brief Avança para o próximo frame da animação.
     */
    virtual void advanceFrame();

    /**
     * @brief Destrutor da spritesheet.
     */
    ~Spritesheet();
};

/**
 * @brief Classe para spritesheets que são ativadas por gatilho e possuem ciclos.
 */
class TriggerSpritesheet : public Spritesheet
{
private:
    bool active = false;
    int cycles = 1;
    int currentCycle = 0;

public:
    /**
     * @brief Construtor da TriggerSpritesheet.
     * @param dir Caminho do arquivo da spritesheet.
     * @param count Quantidade de frames.
     * @param frameW Largura de cada frame.
     * @param frameH Altura de cada frame.
     * @param gap Espaço entre frames.
     */
    TriggerSpritesheet(const char *dir, int count, int frameW, int frameH, int gap);

    /**
     * @brief Construtor alternativo da TriggerSpritesheet.
     * @param dir Caminho do arquivo da spritesheet.
     * @param count Quantidade de frames.
     * @param frameW Largura de cada frame.
     * @param gap Espaço entre frames.
     */
    TriggerSpritesheet(const char *dir, int count, int frameW, int gap);

    /**
     * @brief Define o número de ciclos da animação.
     * @param n Número de ciclos.
     */
    void setCycleCount(int n);

    /**
     * @brief Retorna o número de ciclos definidos.
     * @return int Número de ciclos.
     */
    int getCycleCount() const;

    /**
     * @brief Reinicia a animação e os ciclos.
     */
    void resetAnimation() override;

    /**
     * @brief Avança para o próximo frame, considerando os ciclos.
     */
    void advanceFrame() override;

    /**
     * @brief Verifica se a animação está ativa.
     * @return true Se ativa.
     * @return false Se inativa.
     */
    bool isActive() const;
};

#endif