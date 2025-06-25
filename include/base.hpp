#ifndef BASE_H
#define BASE_H
#include <set>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

/// @brief Número máximo de perfis permitidos.
const int NUMPROFILES = 7;

using namespace std;

/**
 * @brief Classe que representa o perfil de um jogador.
 */
class Profile
{
private:
    string name;     ///< Nome do jogador.
    string nickname; ///< Apelido do jogador.
    int maxDistance; ///< Maior distância alcançada.
    int plays;       ///< Número de partidas jogadas.

public:
    /**
     * @brief Construtor padrão.
     */
    Profile();

    /**
     * @brief Construtor para novo jogador registrado.
     * @param name Nome do jogador.
     * @param nickname Apelido do jogador.
     */
    Profile(string, string);

    /**
     * @brief Construtor para inicializar lista de jogadores.
     * @param name Nome do jogador.
     * @param nickname Apelido do jogador.
     * @param maxDistance Maior distância.
     * @param plays Número de partidas.
     */
    Profile(string, string, int, int);

    /**
     * @brief Construtor de cópia.
     * @param other Outro objeto Profile.
     */
    Profile(const Profile &);

    /**
     * @brief Operador de comparação maior.
     * @param other Outro objeto Profile.
     * @return true se este perfil for maior.
     */
    bool operator>(const Profile &) const;

    /**
     * @brief Operador de comparação menor.
     * @param other Outro objeto Profile.
     * @return true se este perfil for menor.
     */
    bool operator<(const Profile &) const;

    /**
     * @brief Operador de igualdade.
     * @param other Outro objeto Profile.
     * @return true se os perfis forem iguais.
     */
    bool operator==(const Profile &) const;

    /**
     * @brief Operador de atribuição.
     * @param other Outro objeto Profile.
     * @return Profile& Referência para este objeto.
     */
    Profile operator=(const Profile &);

    /// @brief Retorna o nome do jogador.
    string getName();

    /// @brief Retorna o nickname do jogador.
    string getNickname();

    /// @brief Retorna o número de partidas jogadas.
    int getPlays();

    /// @brief Retorna a maior distância alcançada.
    int getMaxDistance();

    /// @brief Define o número de partidas jogadas.
    void setPlays(int);

    /// @brief Define a maior distância alcançada.
    void setMaxDistance(int);

    /// @brief Exibe as informações do perfil.
    void display();
};

/**
 * @brief Classe que representa a base de dados de perfis.
 */
class Base
{
private:
    vector<Profile *> profiles; ///< Vetor de ponteiros para perfis.

    /**
     * @brief Limpa todos os perfis da base.
     */
    void clearProfiles();

    /**
     * @brief Copia perfis de outro vetor.
     * @param profiles Vetor de perfis a ser copiado.
     */
    void copyProfiles(const vector<Profile *> &);

public:
    /**
     * @brief Construtor de cópia.
     * @param other Outro objeto Base.
     */
    Base(const Base &);

    /**
     * @brief Construtor a partir de um vetor de perfis.
     * @param profiles Vetor de ponteiros para perfis.
     */
    Base(const vector<Profile *> &);

    /**
     * @brief Construtor padrão.
     */
    Base();

    /**
     * @brief Construtor que carrega base de um arquivo.
     * @param filename Nome do arquivo.
     */
    Base(string);

    /**
     * @brief Destrutor.
     */
    ~Base();

    /**
     * @brief Operador de atribuição.
     * @param other Outro objeto Base.
     * @return Base& Referência para este objeto.
     */
    Base operator=(const Base &);

    /**
     * @brief Verifica se um nickname está na base.
     * @param nickname Nickname a ser verificado.
     * @return true se está na base.
     */
    bool inBase(string);

    /**
     * @brief Verifica se um perfil está na base.
     * @param profile Perfil a ser verificado.
     * @return true se está na base.
     */
    bool inBase(Profile);

    /**
     * @brief Atualiza ou adiciona um perfil na base.
     * @param profile Perfil a ser atualizado/adicionado.
     * @return true se atualizado/adicionado com sucesso.
     */
    bool updateProfiles(Profile);

    /**
     * @brief Remove um perfil da base pelo nickname.
     * @param nickname Nickname do perfil a ser removido.
     * @return true se removido com sucesso.
     */
    bool removeProfile(string);

    /**
     * @brief Retorna os melhores perfis da base.
     * @return vector<Profile *> Vetor dos melhores perfis.
     */
    vector<Profile *> getBestProfiles();

    /**
     * @brief Salva a base em um arquivo.
     * @param filename Nome do arquivo.
     */
    void saveBase(string);

    /**
     * @brief Exibe todos os perfis da base.
     */
    void display();
};

/**
 * @brief Valida os caracteres do nickname.
 * @param nickname Nickname a ser validado.
 * @return true se válido.
 */
bool validateNicknameChars(string);

/**
 * @brief Valida os caracteres do nome.
 * @param name Nome a ser validado.
 * @return true se válido.
 */
bool validateNameChars(string);

/**
 * @brief Valida o tamanho do nickname.
 * @param nickname Nickname a ser validado.
 * @return true se válido.
 */
bool validateNicknameSize(string);

/**
 * @brief Valida o tamanho do nome.
 * @param name Nome a ser validado.
 * @return true se válido.
 */
bool validateNameSize(string);

#endif