#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "base.hpp"
#include "table.hpp"

/**
 * @brief Classe responsável por gerenciar e exibir o placar de líderes (leaderboard).
 */
class LeaderBoard
{
private:
    Base base;                     ///< Base de dados de perfis.
    vector<Profile *> topProfiles; ///< Vetor com os melhores perfis.

public:
    Table table; ///< Tabela para exibição do leaderboard.

    /**
     * @brief Construtor do LeaderBoard.
     * @param filename Nome do arquivo da base de dados.
     * @param rect Retângulo para exibição da tabela.
     */
    LeaderBoard(string filename, RectangleT rect);

    /**
     * @brief Adiciona um novo perfil ao leaderboard.
     * @param profile Perfil a ser adicionado.
     * @return true se adicionado com sucesso.
     */
    bool addNewProfile(Profile profile);

    /**
     * @brief Atualiza o leaderboard com os melhores perfis.
     */
    void updateLeaderBoard();

    // void setTitleRowColor(Color);

    /**
     * @brief Define a cor da primeira linha.
     * @param color Cor a ser definida.
     */
    void setFirstRowColor(Color color);

    /**
     * @brief Define a cor da segunda linha.
     * @param color Cor a ser definida.
     */
    void setSecondRowColor(Color color);

    /**
     * @brief Define a cor da terceira linha.
     * @param color Cor a ser definida.
     */
    void setThirdRowColor(Color color);

    /**
     * @brief Define a cor das demais linhas.
     * @param color Cor a ser definida.
     */
    void setOthersRowsColor(Color color);

    // void setTitleRowTextColor(Color);

    /**
     * @brief Define a cor do texto da primeira linha.
     * @param color Cor a ser definida.
     */
    void setFirstRowTextColor(Color color);

    /**
     * @brief Define a cor do texto da segunda linha.
     * @param color Cor a ser definida.
     */
    void setSecondRowTextColor(Color color);

    /**
     * @brief Define a cor do texto da terceira linha.
     * @param color Cor a ser definida.
     */
    void setThirdRowTextColor(Color color);

    /**
     * @brief Define a cor do texto das demais linhas.
     * @param color Cor a ser definida.
     */
    void setOthersRowsTextColor(Color color);

    /**
     * @brief Desenha o leaderboard na tela.
     * @param font Fonte a ser utilizada.
     */
    void drawLeaderBoard(ALLEGRO_FONT *font);

    /**
     * @brief Exibe o leaderboard no console.
     */
    void display();

    /**
     * @brief Salva o leaderboard em um arquivo.
     * @param filename Nome do arquivo.
     */
    void save(string filename);
};

#endif
