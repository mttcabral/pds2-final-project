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
        return p2-p1;
    }
    Point getNormalVector() const {
        return Point(-y,x);
    }
    float dotProduct(const Point &p2) const {
        return x * p2.x + y * p2.y;
    }
    Point normalizeVector() const {
        double len = std::sqrt(x * x + y * y);
        return (len != 0) ? Point(x / len, y / len) : Point(0, 0);
    }
    Point rotateVector(float angle) const;
    Point rotateVector(float cosA, float sinA) const;
    Point rotatePoint(const Point&rotationCenter, float angle) const;
    Point rotatePoint(const Point&rotationCenter, float cosA, float sinA) const;
};

ostream& operator<<(std::ostream& os, const Point& p);

struct Polygon{
    vector<Point> vertices;
    int vertexCount;
    float angle = 0;
    set<Point> edgeVectors;
    set<Point> edgeNormals;

    //these functions take into account possible polygon rotation
    vector<Point> getRotatedVertices(const Point& center); 
    set<Point> getEdgeVectors();
    set<Point> getEdgeNormals();
    //get possibly modified polygon
    virtual Polygon getPolygon(const Point &center = Point(0,0));

    Polygon(initializer_list<Point> vert): vertices(vert) {
        vertexCount = vertices.size();

        for (int i = 0; i < vertexCount; i++) {
            Point nextVertex = vertices[(i+1) % vertexCount];
            Point edge = Point::getEdgeVector(vertices[i],nextVertex);

            edgeVectors.insert(edge);
            edgeNormals.insert(edge.getNormalVector().normalizeVector());
        }
    }
    Polygon(const std::vector<Point> &vert): vertices(vert) {
        vertexCount = vertices.size();

        for (int i = 0; i < vertexCount; i++) {
            Point nextVertex = vertices[(i+1) % vertexCount];
            Point edge = Point::getEdgeVector(vertices[i],nextVertex);

            edgeVectors.insert(edge);
            edgeNormals.insert(edge.getNormalVector().normalizeVector());
        }
    }
    Polygon(vector<Point>vert, int n , set<Point>vect, set<Point>normals): 
            vertices(vert), vertexCount(n), angle(0), edgeVectors(vect), edgeNormals(normals) {}

    Polygon(const Polygon &copy): vertices(copy.vertices), vertexCount(copy.vertexCount),
                                angle(copy.angle), edgeVectors(copy.edgeVectors), 
                                edgeNormals(copy.edgeNormals) {}

    void operator=(const Polygon &copy) {
        this->vertices = copy.vertices;
        this->vertexCount = copy.vertexCount;
        this->angle = copy.angle;
        this->edgeVectors = copy.edgeVectors;
        this->edgeNormals = copy.edgeNormals;
    }
    float *getPointArray();

    void addAngle(float radians);

    virtual void updateVertices(const Point& delta);
};

ostream& operator<<(std::ostream& os, const Polygon& p);

// for rouding errors in calculations
const float EPSILON = 1e-5;
bool isAlmostEqual(float a, float b, float epsilon = EPSILON);

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

//checks if two polygons colides using Separated Axes Theorem
//remember to always pass as parameters p.getPolygon()!!!!!!!!!!!!!
bool isColidingSAT(const Polygon &a, const Polygon &b);

struct Rectangle : Polygon {
    float width, height;
    Point center;

    Rectangle(const Point &center, float w, float h);

    //autmatically gets vertices even if rotated in some way, centered in center
    //Use normal getRotatedVertices() if rotation center != polygon center of mass
    vector<Point> getVertices();

    Polygon getPolygon(const Point &center = Point(0,0)) override;
    
    void updateVertices(const Point& delta) override;
};

struct RegularPolygon : Polygon {
    Point center;
    int EdgeCount;
    float edgeLength;

    RegularPolygon(const Point &center,int n, float length);

    //see notes in Rectangle struct
    vector<Point> getVertices();
    Polygon getPolygon(const Point &center = Point(0,0)) override;

    void updateVertices(const Point& delta) override;
};

std::vector<Point> calculateRectangle(const Point &center, float w, float h);

std::vector<Point> calculateRegularPolygon(const Point &center,int n, float edge);

float* vectorToFloatArray(const std::vector<Point>& points); 



#endif
