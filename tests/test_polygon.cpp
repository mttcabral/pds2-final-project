#include "doctest.h"
#include "polygon.hpp"

TEST_CASE("Testando a Struct Point")
{
    Point p1(1.0f, 2.0f);
    Point p2(3.0f, 4.0f);

    SUBCASE("Operadores")
    {
        Point p_add = p1 + p2;
        CHECK(p_add.x == doctest::Approx(4.0f));
        CHECK(p_add.y == doctest::Approx(6.0f));

        Point p_sub = p2 - p1;
        CHECK(p_sub.x == doctest::Approx(2.0f));
        CHECK(p_sub.y == doctest::Approx(2.0f));
    }

    SUBCASE("Operações de Vetor")
    {
        Point edge = Point::getEdgeVector(p1, p2);
        CHECK(edge.x == doctest::Approx(2.0f));
        CHECK(edge.y == doctest::Approx(2.0f));

        Point normal = edge.getNormalVector();
        CHECK(normal.x == doctest::Approx(-2.0f));
        CHECK(normal.y == doctest::Approx(2.0f));

        float dot = p1.dotProduct(p2);
        CHECK(dot == doctest::Approx(11.0f));
    }

    SUBCASE("Rotação")
    {
        Point p(1.0f, 0.0f);
        Point rotated = p.rotateVector(PI / 2); // 90 graus
        CHECK(rotated.x == doctest::Approx(0.0f).epsilon(0.001));
        CHECK(rotated.y == doctest::Approx(1.0f).epsilon(0.001));

        Point to_rotate(5.0f, 5.0f);
        Point center(2.0f, 2.0f);
        Point rotated_point = to_rotate.rotatePoint(center, PI); // 180 graus
        CHECK(rotated_point.x == doctest::Approx(-1.0f).epsilon(0.001));
        CHECK(rotated_point.y == doctest::Approx(-1.0f).epsilon(0.001));
    }
}

TEST_CASE("Testando as Structs de Polígono")
{
    Point center(0.0f, 0.0f);
    SUBCASE("Retângulo")
    {
        Rectangle rect(center, 10.0f, 20.0f);
        CHECK(rect.vertexCount == 4);
        CHECK(rect.width == 10.0f);
        CHECK(rect.height == 20.0f);

        auto vertices = rect.vertices;
        CHECK(vertices[0].x == doctest::Approx(5.0f));
        CHECK(vertices[0].y == doctest::Approx(-10.0f));
    }

    SUBCASE("Polígono Regular")
    {
        RegularPolygon pentagon(center, 5, 10.0f);
        CHECK(pentagon.vertexCount == 5);
        CHECK(pentagon.EdgeCount == 5);
        CHECK(pentagon.edgeLength == 10.0f);
    }
}

TEST_CASE("Testando Colisão SAT")
{
    Rectangle r1({0, 0}, 2, 2);
    Rectangle r2({1, 0}, 2, 2);
    Rectangle r3({3, 0}, 2, 2);

    Polygon p1 = r1.getPolygon();
    Polygon p2 = r2.getPolygon();
    Polygon p3 = r3.getPolygon();

    CHECK(isColidingSAT(p1, p2));
    CHECK_FALSE(isColidingSAT(p1, p3));

    r2.addAngle(PI / 4); // rotaciona 45 graus
    Polygon p2_rotated = r2.getPolygon();
    CHECK(isColidingSAT(p1, p2_rotated));
}