#ifndef REGISTER_H
#define REGISTER_H
#include <vector>
#include <stdbool.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "table.hpp"
#include <set>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/// @brief Tamanho mínimo do nome do perfil.
const int MINPROFILENAMESIZE = 4;
/// @brief Tamanho máximo do nome do perfil.
const int MAXPROFILENAMESIZE = 20;

/// @brief Tamanho mínimo do nickname do perfil.
const int MINPROFILENICKNAMESIZE = 4;
/// @brief Tamanho máximo do nickname do perfil.
const int MAXPROFILENICKNAMESIZE = 12;

/// @brief Número de linhas do registro.
int const NUMREGISTERROWS = 3;

/**
 * @brief Classe responsável pelo registro de novos perfis.
 */
class Register
{
private:
    int bufferSize;   ///< Tamanho do buffer de entrada.
    char *buffer;     ///< Buffer de caracteres digitados.
    int index;        ///< Índice atual do buffer.
    string tittle;    ///< Título do registro.
    string message;   ///< Mensagem de feedback.
    RectangleT plan;  ///< Retângulo de exibição.
    vector<Row> rows; ///< Linhas do formulário.

public:
    /**
     * @brief Construtor do registro.
     * @param bufferSize Tamanho do buffer.
     * @param plan Retângulo de exibição.
     */
    Register(int bufferSize, RectangleT plan);

    /**
     * @brief Construtor do registro com título.
     * @param tittle Título do registro.
     * @param bufferSize Tamanho do buffer.
     * @param plan Retângulo de exibição.
     */
    Register(string tittle, int bufferSize, RectangleT plan);

    /**
     * @brief Destrutor do registro.
     */
    ~Register();

    /**
     * @brief Construtor de cópia.
     * @param other Outro objeto Register.
     */
    Register(const Register &other);

    /**
     * @brief Operador de atribuição.
     * @param other Outro objeto Register.
     * @return Referência para este objeto.
     */
    Register &operator=(const Register &other);

    /**
     * @brief Escreve um caractere no buffer.
     * @param c Caractere a ser escrito.
     * @return true se escrito com sucesso.
     */
    bool writeInBuffer(char c);

    /**
     * @brief Remove o último caractere do buffer.
     * @return true se removido com sucesso.
     */
    bool deleteInBuffer();

    /**
     * @brief Limpa o buffer.
     * @return true se limpo com sucesso.
     */
    bool cleanBuffer();

    /**
     * @brief Retorna o conteúdo do título.
     * @return Conteúdo do título.
     */
    string getTittleContent();

    /**
     * @brief Retorna o conteúdo da mensagem.
     * @return Conteúdo da mensagem.
     */
    string getMessageContent();

    /**
     * @brief Retorna o conteúdo do buffer.
     * @return Conteúdo do buffer.
     */
    string getBufferContent();

    /**
     * @brief Retorna o conteúdo da i-ésima linha.
     * @param i Índice da linha.
     * @return Conteúdo da linha.
     */
    string getIthContent(int i);

    /**
     * @brief Retorna a cor do texto do título.
     * @return Cor do texto.
     */
    Color getTittleTextColor();

    /**
     * @brief Retorna a cor do texto da mensagem.
     * @return Cor do texto.
     */
    Color getMessageTextColor();

    /**
     * @brief Retorna a cor do texto do buffer.
     * @return Cor do texto.
     */
    Color getBufferTextColor();

    /**
     * @brief Retorna a cor do texto da i-ésima linha.
     * @param i Índice da linha.
     * @return Cor do texto.
     */
    Color getIthTextColor(int i);

    /**
     * @brief Retorna a coordenada X central da i-ésima linha.
     * @param i Índice da linha.
     * @return Coordenada X.
     */
    float getIthCenterX(int i);

    /**
     * @brief Retorna a coordenada Y central da i-ésima linha.
     * @param i Índice da linha.
     * @return Coordenada Y.
     */
    float getIthCenterY(int i);

    /**
     * @brief Define o conteúdo do título.
     * @param tittle Novo título.
     */
    void setTittleContent(string tittle);

    /**
     * @brief Define o conteúdo da mensagem.
     * @param message Nova mensagem.
     */
    void setMessageContent(string message);

    /**
     * @brief Define a cor do texto do título.
     * @param color Nova cor.
     */
    void setTittleTextColor(Color color);

    /**
     * @brief Define a cor do texto da mensagem.
     * @param color Nova cor.
     */
    void setMessageTextColor(Color color);

    /**
     * @brief Define a cor do texto do buffer.
     * @param color Nova cor.
     */
    void setBufferTextColor(Color color);

    /**
     * @brief Desenha o formulário de registro na tela.
     * @param font1 Fonte principal.
     * @param font2 Fonte secundária.
     */
    void drawRegister(ALLEGRO_FONT *font1, ALLEGRO_FONT *font2);
};

/**
 * @brief Valida os caracteres do nome.
 * @param name Nome a ser validado.
 * @return true se válido.
 */
bool validateNameChars(string name);

/**
 * @brief Valida os caracteres do nickname.
 * @param nickname Nickname a ser validado.
 * @return true se válido.
 */
bool validateNicknameChars(string nickname);

/**
 * @brief Valida o tamanho do nome.
 * @param name Nome a ser validado.
 * @return true se válido.
 */
bool validateNameSize(string name);

/**
 * @brief Valida o tamanho do nickname.
 * @param nickname Nickname a ser validado.
 * @return true se válido.
 */
bool validateNicknameSize(string nickname);

/**
 * @brief Valida o nome completo.
 * @param name Nome a ser validado.
 * @return true se válido.
 */
bool validateName(string name);

/**
 * @brief Valida o nickname completo.
 * @param nickname Nickname a ser validado.
 * @return true se válido.
 */
bool validateNickname(string nickname);

/**
 * @brief Verifica o nome e retorna mensagem de erro.
 * @param name Nome a ser verificado.
 * @param msg Mensagem de erro.
 * @return true se válido.
 */
bool checkName(string name, string &msg);

/**
 * @brief Verifica o nickname e retorna mensagem de erro.
 * @param nickname Nickname a ser verificado.
 * @param msg Mensagem de erro.
 * @return true se válido.
 */
bool checkNickname(string nickname, string &msg);

#endif