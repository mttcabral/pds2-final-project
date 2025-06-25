#ifndef COOLDOWN_H
#define COOLDOWN_H

/// @brief Classe para controle de eventos temporais, como cooldowns de ações ou geração de obstáculos.
/// @details Mantenha sincronizado com o FPS principal do jogo.
const float FPS = 30;

/**
 * @brief Classe que gerencia cooldowns temporais.
 */
class Cooldown
{
private:
    float timeLeft = 0;        ///< Frames restantes para finalizar o cooldown.
    float rechargeTime;        ///< Tempo necessário para recarregar o cooldown.
    float updateFrequency = 1; ///< Fator de velocidade da contagem do cooldown.
    bool frozen = false;       ///< Indica se o cooldown está congelado.

public:
    /**
     * @brief Construtor que define o tempo de recarga em segundos.
     * @param wuTime Tempo de recarga em segundos.
     */
    Cooldown(float wuTime);

    /**
     * @brief Construtor padrão.
     */
    Cooldown();

    /**
     * @brief Atualiza o cooldown, reduzindo o tempo restante.
     */
    void updateCooldown();

    /**
     * @brief Reinicia o cooldown para o tempo de recarga.
     */
    void restartCooldown();

    /**
     * @brief Define o cooldown como pronto imediatamente.
     */
    void refreshCooldown();

    /**
     * @brief Verifica se o cooldown terminou.
     * @return true se terminou, false caso contrário.
     */
    bool isCooldownUp();

    /**
     * @brief Define um novo tempo de recarga (em segundos).
     * @param wuTime Novo tempo de recarga.
     */
    void setRechargeTime(float wuTime);

    /**
     * @brief Define um novo fator de velocidade de atualização.
     * @param f Novo fator de atualização.
     */
    void setUpdateFrequency(float f);

    /**
     * @brief Retorna o tempo restante atual do cooldown.
     * @return Tempo restante.
     */
    float getCurrentTimeLeft();

    /**
     * @brief Retorna a porcentagem do cooldown já decorrido.
     * @return Porcentagem (0 a 1).
     */
    float getCurrentPorcentage();

    /**
     * @brief Retorna o tempo total de recarga.
     * @return Tempo de recarga.
     */
    float getRechargeTime();

    /**
     * @brief Congela o cooldown (pausa a contagem).
     */
    void freezeCooldown();

    /**
     * @brief Descongela o cooldown (retoma a contagem).
     */
    void unfreezeCooldown();
};

#endif