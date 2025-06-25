#ifndef POLYGON_H
#define POLYGON_H
#include <cmath>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

/// @brief Valor de PI calculado com arccos(-1).
const float PI = acos(-1.0); // PI calculated with arccos(-1)

// Vector/Point struct, contains a pair of two float coordinates
/**
 * @brief Estrutura que representa um ponto ou vetor 2D.
 */
struct Point
{
    float x, y;

    /**
     * @brief Construtor que inicializa as coordenadas.
     * @param x Coordenada X.
     * @param y Coordenada Y.
     */
    Point(float x, float y) : x(x), y(y) {}

    /**
     * @brief Construtor padrão (x=0, y=0).
     */
    Point() : x(0), y(0) {}

    /**
     * @brief Soma de pontos/vetores.
     */
    Point operator+(const Point &p2) const
    {
        return Point(x + p2.x, y + p2.y);
    }

    /**
     * @brief Subtração de pontos/vetores.
     */
    Point operator-(const Point &p2) const
    {
        return Point(x - p2.x, y - p2.y);
    }

    /**
     * @brief Operador de comparação para ordenação.
     */
    bool operator<(const Point &p2) const
    {
        return (x != p2.x) ? x < p2.x : y < p2.y;
    }

    /**
     * @brief Retorna o vetor aresta entre dois pontos.
     */
    static Point getEdgeVector(const Point &p1, const Point &p2)
    {
        return p2 - p1;
    }

    /**
     * @brief Retorna o vetor normal ao vetor atual.
     */
    Point getNormalVector() const
    {
        return Point(-y, x);
    }

    /**
     * @brief Produto escalar entre dois vetores.
     */
    float dotProduct(const Point &p2) const
    {
        return x * p2.x + y * p2.y;
    }

    /**
     * @brief Normaliza o vetor.
     */
    Point normalizeVector() const
    {
        double len = std::sqrt(x * x + y * y);
        return (len != 0) ? Point(x / len, y / len) : Point(0, 0);
    }

    /**
     * @brief Rotaciona o vetor por um ângulo.
     * @param angle Ângulo em radianos.
     * @return Vetor rotacionado.
     */
    Point rotateVector(float angle) const;

    /**
     * @brief Rotaciona o vetor usando cosseno e seno.
     */
    Point rotateVector(float cosA, float sinA) const;

    /**
     * @brief Rotaciona o ponto em torno de um centro.
     * @param rotationCenter Centro de rotação.
     * @param angle Ângulo em radianos.
     */
    Point rotatePoint(const Point &rotationCenter, float angle) const;

    /**
     * @brief Rotaciona o ponto em torno de um centro usando cosseno e seno.
     */
    Point rotatePoint(const Point &rotationCenter, float cosA, float sinA) const;
};

/**
 * @brief Sobrecarga do operador de saída para Point.
 */
ostream &operator<<(std::ostream &os, const Point &p);

// Polygon defined by a set of vertices that represent it's size and shape
/**
 * @brief Estrutura que representa um polígono genérico.
 */
struct Polygon
{
    vector<Point> vertices;
    int vertexCount;
    float angle = 0;
    set<Point> edgeVectors;
    set<Point> edgeNormals;

    // these functions take into account possible polygon rotation
    /**
     * @brief Retorna os vértices rotacionados em torno de um centro.
     * @param center Centro de rotação.
     */
    vector<Point> getRotatedVertices(const Point &center);

    /**
     * @brief Retorna o conjunto de vetores das arestas.
     */
    set<Point> getEdgeVectors();

    /**
     * @brief Retorna o conjunto de vetores normais das arestas.
     */
    set<Point> getEdgeNormals();

    // get possibly modified polygon
    /**
     * @brief Retorna o polígono (possivelmente modificado).
     * @param center Centro de referência.
     */
    virtual Polygon getPolygon(const Point &center = Point(0, 0));

    /**
     * @brief Construtor a partir de lista de vértices.
     */
    Polygon(initializer_list<Point> vert) : vertices(vert)
    {
        vertexCount = vertices.size();

        for (int i = 0; i < vertexCount; i++)
        {
            Point nextVertex = vertices[(i + 1) % vertexCount];
            Point edge = Point::getEdgeVector(vertices[i], nextVertex);

            edgeVectors.insert(edge);
            edgeNormals.insert(edge.getNormalVector().normalizeVector());
        }
    }

    /**
     * @brief Construtor a partir de vetor de vértices.
     */
    Polygon(const std::vector<Point> &vert) : vertices(vert)
    {
        vertexCount = vertices.size();

        for (int i = 0; i < vertexCount; i++)
        {
            Point nextVertex = vertices[(i + 1) % vertexCount];
            Point edge = Point::getEdgeVector(vertices[i], nextVertex);

            edgeVectors.insert(edge);
            edgeNormals.insert(edge.getNormalVector().normalizeVector());
        }
    }

    /**
     * @brief Construtor completo.
     */
    Polygon(vector<Point> vert, int n, set<Point> vect, set<Point> normals) : vertices(vert), vertexCount(n), angle(0), edgeVectors(vect), edgeNormals(normals) {}

    /**
     * @brief Construtor de cópia.
     */
    Polygon(const Polygon &copy) : vertices(copy.vertices), vertexCount(copy.vertexCount),
                                   angle(copy.angle), edgeVectors(copy.edgeVectors),
                                   edgeNormals(copy.edgeNormals) {}

    /**
     * @brief Operador de atribuição.
     */
    void operator=(const Polygon &copy)
    {
        this->vertices = copy.vertices;
        this->vertexCount = copy.vertexCount;
        this->angle = copy.angle;
        this->edgeVectors = copy.edgeVectors;
        this->edgeNormals = copy.edgeNormals;
    }

    /**
     * @brief Retorna um array de floats com os pontos do polígono.
     */
    float *getPointArray();

    /**
     * @brief Adiciona um ângulo de rotação ao polígono.
     * @param radians Ângulo em radianos.
     */
    void addAngle(float radians);

    /**
     * @brief Atualiza os vértices do polígono.
     * @param delta Deslocamento.
     */
    virtual void updateVertices(const Point &delta);
};

/**
 * @brief Sobrecarga do operador de saída para Polygon.
 */
ostream &operator<<(std::ostream &os, const Polygon &p);

// for rouding errors in calculations
/// @brief Constante para erros de arredondamento em cálculos.
const float EPSILON = 1e-5;

/**
 * @brief Verifica se dois floats são quase iguais.
 * @param a Primeiro valor.
 * @param b Segundo valor.
 * @param epsilon Tolerância.
 * @return true se forem quase iguais.
 */
bool isAlmostEqual(float a, float b, float epsilon = EPSILON);

// Used in SAT colision detection
/**
 * @brief Estrutura para projeção de polígono em um eixo (usada no SAT).
 */
struct PolygonProjection
{
    float minProj;
    float maxProj;

    /**
     * @brief Construtor que projeta um polígono em um eixo.
     * @param poly Polígono.
     * @param projAxis Eixo de projeção.
     */
    PolygonProjection(const Polygon &poly, const Point &projAxis)
    {
        // Point normAxis = projAxis.normalizeVector();

        minProj = poly.vertices[0].dotProduct(projAxis);
        maxProj = minProj;

        for (int i = 1; i < poly.vertexCount; i++)
        {
            float testedProj = poly.vertices[i].dotProduct(projAxis);

            if (testedProj < minProj)
                minProj = testedProj;
            if (testedProj > maxProj)
                maxProj = testedProj;
        }
    }

    /**
     * @brief Verifica se há sobreposição entre duas projeções.
     * @param other Outra projeção.
     * @return true se houver sobreposição.
     */
    bool doProjectionOverlap(const PolygonProjection &other)
    {
        return !(maxProj < other.minProj || other.maxProj < minProj);
    }
};

// checks if two polygons colides using Separated Axes Theorem
// remember to always pass as parameters p.getPolygon()!!!!!!!!!!!!! (handles rotation right)
/**
 * @brief Verifica colisão entre dois polígonos usando o Teorema dos Eixos Separados (SAT).
 * @param a Primeiro polígono.
 * @param b Segundo polígono.
 * @return true se houver colisão.
 */
bool isColidingSAT(const Polygon &a, const Polygon &b);

/**
 * @brief Estrutura que representa um retângulo (herda de Polygon).
 */
struct Rectangle : Polygon
{
    float width, height;
    Point center;

    /**
     * @brief Construtor do retângulo.
     * @param center Centro do retângulo.
     * @param w Largura.
     * @param h Altura.
     */
    Rectangle(const Point &center, float w, float h);

    // autmatically gets vertices even if rotated in some way, centered in center
    // Use normal getRotatedVertices() if rotation center != polygon center of mass
    /**
     * @brief Retorna os vértices do retângulo.
     */
    vector<Point> getVertices();

    /**
     * @brief Retorna o polígono do retângulo.
     */
    Polygon getPolygon(const Point &center = Point(0, 0)) override;

    /**
     * @brief Atualiza os vértices do retângulo.
     */
    void updateVertices(const Point &delta) override;
};

/**
 * @brief Estrutura que representa um polígono regular (herda de Polygon).
 */
struct RegularPolygon : Polygon
{
    Point center;
    int EdgeCount;
    float edgeLength;

    /**
     * @brief Construtor do polígono regular.
     * @param center Centro do polígono.
     * @param n Número de lados.
     * @param length Tamanho da aresta.
     */
    RegularPolygon(const Point &center, int n, float length);

    // see notes in Rectangle struct
    /**
     * @brief Retorna os vértices do polígono regular.
     */
    vector<Point> getVertices();

    /**
     * @brief Retorna o polígono regular.
     */
    Polygon getPolygon(const Point &center = Point(0, 0)) override;

    /**
     * @brief Atualiza os vértices do polígono regular.
     */
    void updateVertices(const Point &delta) override;
};

/**
 * @brief Calcula os vértices de um retângulo.
 * @param center Centro do retângulo.
 * @param w Largura.
 * @param h Altura.
 * @return Vetor de pontos.
 */
std::vector<Point> calculateRectangle(const Point &center, float w, float h);

/**
 * @brief Calcula os vértices de um polígono regular.
 * @param center Centro do polígono.
 * @param n Número de lados.
 * @param edge Tamanho da aresta.
 * @return Vetor de pontos.
 */
std::vector<Point> calculateRegularPolygon(const Point &center, int n, float edge);

/**
 * @brief Converte um vetor de pontos em um array de floats.
 * @param points Vetor de pontos.
 * @return Ponteiro para array de floats.
 */
float *vectorToFloatArray(const std::vector<Point> &points);

#endif
