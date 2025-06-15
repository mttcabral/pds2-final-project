#include "game_object.hpp"
#include "hitbox.hpp"
#include "entity.hpp"
#include "cooldown.hpp"
#include <iostream>
#include <string>

void test(Polygon play) {
        vector<Point> vertices1 = {
        {1025, 250},
        {975, 250},
        {975, 550},
        {1025, 550}
    };

    int vertexCount1 = 4;

    set<Point> edgeVectors1 = {
        {-50, 0},
        {0, -300},
        {0, 300},
        {50, 0}
    };

    set<Point> edgeNormals1 = {
        {-1, 0},
        {0, -1},
        {0, 1},
        {1, 0}
    };

    // Creating the polygon object:
    Polygon poly1(vertices1, vertexCount1, edgeVectors1, edgeNormals1);
    
    vector<Point> vertices2 = {
        {1123.74f, 311.612f},
        {1088.39f, 276.256f},
        {876.256f, 488.388f},
        {911.612f, 523.744f}
    };
    
    int vertexCount2 = 4;
    
    set<Point> edgeVectors2 = {
        {-212.132f, 212.132f},
        {-35.3553f, -35.3553f},
        {35.3553f, 35.3553f},
        {212.132f, -212.132f}
    };
    
    set<Point> edgeNormals2 = {
        {-0.707107f, -0.707107f},
        {-0.707107f, 0.707107f},
        {0.707107f, -0.707107f},
        {0.707107f, 0.707107f}
    };
    
    Polygon poly2(vertices2, vertexCount2, edgeVectors2, edgeNormals2);
    poly2.updateVertices(Point(-800,0));

    std::cout << isColidingSAT(poly2,play) << "===========================\n";
}

//play - player when first init - (200,400) regular octagon
//poly1 - normal rectangle at (1000,400)
//poly2 - rotated rectangle at (1000,400) as given by rotation functions
//(copied and pasted from testing and reconstructed in this scenario from zero)

// poly1 e poly2 - 1
// poly1 (deslocado a esquerda) e poly2 - 0
// poly1 e play - 0
// poly1 (-800 no x) e play - 1
// poly2 e play - 0
// poly2 (-800 no x) e play - 1 !!!!!!!!!!!!!!!!!!!! - in normal game is not happening

