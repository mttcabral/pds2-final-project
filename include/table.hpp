#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <stdbool.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/// @brief Número de colunas da tabela.
const int NUMCOLUMNS = 3;
/// @brief Número de linhas da tabela.
const int NUMROWS = 7;

/**
 * @brief Estrutura que representa um ponto 2D para tabelas.
 */
struct PointT
{
private:
    /**
     * @brief Ajusta valor para zero se estiver próximo.
     * @param v Valor a ser ajustado.
     * @return Valor ajustado.
     */
    float toZero(float v);

public:
    float x, y; ///< Coordenadas do ponto.

    /**
     * @brief Construtor padrão.
     */
    PointT();

    /**
     * @brief Construtor com coordenadas.
     * @param x Coordenada X.
     * @param y Coordenada Y.
     */
    PointT(float x, float y);

    /**
     * @brief Construtor de cópia.
     * @param other Outro ponto.
     */
    PointT(const PointT &other);

    /**
     * @brief Operador de atribuição.
     * @param other Outro ponto.
     * @return Referência para este ponto.
     */
    PointT &operator=(const PointT &other);

    /**
     * @brief Subtrai dois pontos.
     * @param other Outro ponto.
     * @return Resultado da subtração.
     */
    PointT operator-(const PointT &other) const;

    /**
     * @brief Soma dois pontos.
     * @param other Outro ponto.
     * @return Resultado da soma.
     */
    PointT operator+(const PointT &other) const;

    /**
     * @brief Divide ponto por escalar.
     * @param f Escalar.
     * @return Resultado da divisão.
     */
    PointT operator/(float f) const;

    /**
     * @brief Multiplica ponto por escalar.
     * @param f Escalar.
     * @return Resultado da multiplicação.
     */
    PointT operator*(float f);

    /**
     * @brief Exibe o ponto no console.
     */
    void display();
};

/**
 * @brief Estrutura que representa uma cor RGB.
 */
struct Color
{
    float r, g, b; ///< Componentes de cor (0 - 255)

    /**
     * @brief Construtor padrão.
     */
    Color();

    /**
     * @brief Construtor com valores RGB.
     * @param r Vermelho.
     * @param g Verde.
     * @param b Azul.
     */
    Color(float r, float g, float b);

    /**
     * @brief Construtor de cópia.
     * @param other Outra cor.
     */
    Color(const Color &other);

    /**
     * @brief Operador de atribuição.
     * @param other Outra cor.
     * @return Referência para esta cor.
     */
    Color &operator=(const Color &other);

    /**
     * @brief Divide cor por escalar.
     * @param f Escalar.
     * @return Resultado da divisão.
     */
    Color operator/(float f) const;

    /**
     * @brief Exibe a cor no console.
     */
    void display();
};

/**
 * @brief Estrutura que representa um retângulo para tabelas.
 */
struct RectangleT
{
    PointT center, topLeft, bottomRight; ///< Pontos principais do retângulo.
    vector<PointT> subCenters;           ///< Subcentros para divisão.
    float length, height;                ///< Dimensões do retângulo.

    /**
     * @brief Construtor padrão.
     */
    RectangleT();

    /**
     * @brief Construtor com centro, comprimento e altura.
     * @param center Centro do retângulo.
     * @param length Comprimento.
     * @param height Altura.
     */
    RectangleT(PointT center, float length, float height);

    /**
     * @brief Construtor com dois pontos.
     * @param topLeft Canto superior esquerdo.
     * @param bottomRight Canto inferior direito.
     */
    RectangleT(PointT topLeft, PointT bottomRight);

    /**
     * @brief Construtor de cópia.
     * @param other Outro retângulo.
     */
    RectangleT(const RectangleT &other);

    /**
     * @brief Operador de atribuição.
     * @param other Outro retângulo.
     * @return Referência para este retângulo.
     */
    RectangleT &operator=(const RectangleT &other);

    /**
     * @brief Exibe o retângulo no console.
     */
    void display();
};

/**
 * @brief Estrutura que representa uma linha da tabela.
 */
struct Row
{
    RectangleT rowRectangle;   ///< Retângulo da linha.
    vector<string> texts;      ///< Textos da linha.
    Color textColor, rowColor; ///< Cores do texto e da linha.

    /**
     * @brief Construtor padrão.
     */
    Row();

    /**
     * @brief Construtor com cores e retângulo.
     * @param textColor Cor do texto.
     * @param rowColor Cor da linha.
     * @param rowRectangle Retângulo da linha.
     */
    Row(Color textColor, Color rowColor, RectangleT rowRectangle);

    /**
     * @brief Construtor com retângulo.
     * @param rowRectangle Retângulo da linha.
     */
    Row(RectangleT rowRectangle);

    /**
     * @brief Construtor com dois pontos.
     * @param topLeft Canto superior esquerdo.
     * @param bottomRight Canto inferior direito.
     */
    Row(PointT topLeft, PointT bottomRight);

    /**
     * @brief Construtor de cópia.
     * @param other Outra linha.
     */
    Row(const Row &other);

    /**
     * @brief Operador de atribuição.
     * @param other Outra linha.
     * @return Referência para esta linha.
     */
    Row &operator=(const Row &other);

    /**
     * @brief Exibe a linha no console.
     */
    void display();
};

/**
 * @brief Estrutura que representa uma tabela.
 */
struct Table
{
    RectangleT tableRectangle; ///< Retângulo da tabela.
    vector<Row> row;           ///< Linhas da tabela.

    /**
     * @brief Construtor padrão.
     */
    Table();

    /**
     * @brief Construtor com retângulo.
     * @param tableRectangle Retângulo da tabela.
     */
    Table(RectangleT tableRectangle);

    /**
     * @brief Construtor de cópia.
     * @param other Outra tabela.
     */
    Table(const Table &other);

    /**
     * @brief Operador de atribuição.
     * @param other Outra tabela.
     * @return Referência para esta tabela.
     */
    Table &operator=(const Table &other);

    /**
     * @brief Exibe a tabela no console.
     */
    void display();
};

#endif
