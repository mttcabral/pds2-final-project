#ifndef POLYGON_H
#define POLYGON_H
#include <cmath>
#include <vector>
#include <set>
#include <iostream>

using namespace std;
const float PI = acos(-1.0); // PI calculated with arccos(-1)

struct Point{
    float x,y;

    Point(float x, float y): x(x), y(y) {}
    Point(): x(0), y(0) {}

    Point operator+(const Point &p2) const{
        return Point(x+p2.x,y+p2.y);
    }
    Point operator-(const Point &p2) const{
        return Point(x-p2.x,y-p2.y);
    }
    bool operator<(const Point &p2) const{
        return (x != p2.x) ? x < p2.x : y < p2.y;
    }
    static Point getEdgeVector(const Point &p1, const Point &p2){
        return p1-p2;
    }
    Point getNormalVector() {
        return Point(-y,x);
    }
    float dotProduct(const Point &p2) const {
        return x * p2.x + y * p2.y;
    }
    Point normalizeVector() const {
        double len = std::sqrt(x * x + y * y);
        return (len != 0) ? Point(x / len, y / len) : Point(0, 0);
    }
    Point rotatePoint(const Point&rotationCenter, float angle);
};



struct Polygon{
    std::vector<Point> vertices;
    int vertexCount;
    std::set<Point> edgeVectors;
    std::set<Point> edgeNormals;

    Polygon(std::initializer_list<Point> vert): vertices(vert) {
        vertexCount = vertices.size();

        for (int i = 0; i < vertexCount; i++) {
            Point nextVertex = vertices[i+1 == vertexCount ? 0 : i+1];
            Point edge = Point::getEdgeVector(vertices[i],nextVertex);

            edgeVectors.insert(edge);
            edgeNormals.insert(edge.getNormalVector().normalizeVector());
        }
    }
    Polygon(const std::vector<Point> &vert): vertices(vert) {
        vertexCount = vertices.size();

        for (int i = 0; i < vertexCount; i++) {
            Point nextVertex = vertices[i+1 == vertexCount ? 0 : i+1];
            Point edge = Point::getEdgeVector(vertices[i],nextVertex);

            edgeVectors.insert(edge);
            edgeNormals.insert(edge.getNormalVector());
        }
    }
    float *getPointArray();
    //recalculate vectors

    //rotate

    void updateVertices(const Point& delta);
};

struct PolygonProjection{
    float minProj;
    float maxProj;

    PolygonProjection(const Polygon &poly, const Point & projAxis) {
        //Point normAxis = projAxis.normalizeVector();

        minProj = poly.vertices[0].dotProduct(projAxis);
        maxProj = minProj;

        for (int i = 1; i < poly.vertexCount; i++) {
            float testedProj = poly.vertices[i].dotProduct(projAxis);

            if (testedProj < minProj) minProj = testedProj;
            if (testedProj > maxProj) maxProj = testedProj;
        }
    }

    bool doProjectionOverlap(const PolygonProjection &other) {
        return !(maxProj < other.minProj || other.maxProj < minProj);
    }
};

bool isColidingSAT(const Polygon &a, const Polygon &b);

struct Rectangle : Polygon {
    float width, height;
    Point center;

    Rectangle(const Point &center, float w, float h);
    
};

struct RegularPolygon : Polygon {
    Point center;
    int EdgeCount;
    float edgeLength;

    RegularPolygon(const Point &center,int n, float length);
};

std::vector<Point> calculateRectangle(const Point &center, float w, float h);

std::vector<Point> calculateRegularPolygon(const Point &center,int n, float edge);

float* vectorToFloatArray(const std::vector<Point>& points); 



#endif
