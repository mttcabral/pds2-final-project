#include "polygon.hpp"

using namespace std;

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

bool isColidingSAT(const Polygon &a, const Polygon &b) {
    
    set<Point> axes;

    for (auto n : a.edgeNormals) axes.insert(n);
    for (auto n : b.edgeNormals) axes.insert(n);

    for (auto axis : axes) {

        PolygonProjection projectionA(a,axis);
        PolygonProjection projectionB(b,axis);

        if (!projectionA.doProjectionOverlap(projectionB)) return false;
        //else continue;
    }
    return true;
}
//Basic SAT - Separated Axis Theorem
//checks for all projection Axes, if none have gaps between both polygon projections, then it colides
//if at least one comparison between polygon projections contains a gap (not(overlap(pA,pB)))
//Then the objects do not colide

void Polygon::addAngle(float radians) {
    float output = radians + this->angle;
    if (isAlmostEqual(output,0)) this->angle = 0;
    else this->angle = output;
}

Point Point::rotateVector(float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    return Point(this->x * cosA - this->y * sinA,
                 this->x * sinA + this->y * cosA);
}
Point Point::rotateVector(float cosA, float sinA) {
    return Point(this->x * cosA - this->y * sinA,
                 this->x * sinA + this->y * cosA);
}

Point Point::rotatePoint(const Point& rotationCenter, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    
    Point dPoint = *this - rotationCenter;

    return Point(dPoint.x * cosA - dPoint.y * sinA + rotationCenter.x,
                 dPoint.x * sinA + dPoint.y * cosA + rotationCenter.y);

}
Point Point::rotatePoint(const Point& rotationCenter, float cosA, float sinA) {
    Point dPoint = *this - rotationCenter;
    return Point(dPoint.x * cosA - dPoint.y * sinA + rotationCenter.x,
                 dPoint.x * sinA + dPoint.y * cosA + rotationCenter.y);

}
//WARNING : 
//It is important that switching to double precision be considered in this, to avoid rouding errors
//Avoid repeated rotations :
//Maybe keep a value "rotatedAngle" in polygon so that this is changed in every loop
//And then calculate the actual rotated points/vectors from 0 and not from stacked rotations


vector<Point> Polygon::getRotatedVertices(const Point &center){
    if (angle == 0) return vertices;
    else {
        vector<Point> out;
        float cosine = cos(angle);
        float sine = sin(angle);
        for (auto p : this->vertices) 
            out.push_back(p.rotatePoint(center,cosine,sine));
        return out;
    }
}
// write 'overrides' to simplify center adding
vector<Point> Rectangle::getVertices() {
    return this->getRotatedVertices(this->center);
}
vector<Point> RegularPolygon::getVertices() {
    return this->getRotatedVertices(this->center);
}

set<Point> Polygon::getEdgeVectors() {
    if (angle == 0) return edgeVectors;
    else {
        float cosine = cos(angle);
        float sine = sin(angle);
        set<Point> out;
        for (auto vector : edgeVectors) out.insert(vector.rotateVector(cosine,sine));
        return out;
    }
}
set<Point> Polygon::getEdgeNormals(){
    if (angle == 0) return edgeNormals;
    else {
        float cosine = cos(angle);
        float sine = sin(angle);
        set<Point> out;
        for (Point vector : edgeNormals) out.insert(vector.rotateVector(cosine,sine));
        return out;
    }
}

bool isAlmostEqual(float a, float b, float epsilon) {
    return abs(a-b) <= epsilon;
}

Polygon Polygon::getPolygon(){
    if (angle == 0) return *this;
    else {
        // placeholder, will do this later
        // polygon needs to have a copy constructor in order to do this well
        // after is done, replace instances of 'const Polygon&' parameters with this funcion
    }
}

vector<Point> calculateRectangle(const Point &center, float w, float h) {
    Point aux1(w/2,h/2);
    Point aux2(w/2,-h/2);
    return {center - aux1, center + aux1, 
            center - aux2, center + aux2};
}
Rectangle::Rectangle(const Point &center, float w, float h): Polygon(calculateRectangle(center,w,h)),
                                                            width(w), height(h), center(center) {}

float *Polygon::getPointArray() {
        return vectorToFloatArray(this->vertices);
    }

vector<Point> calculateRegularPolygon(const Point &center,int n, float edge){
    vector<Point> vertices;

    if (n < 3) return vertices;

    //radius of circumscribed circunference
    float radius = edge / (2 * sin(PI/n));

    //for each vertex, calculate angle and vertex coordinate based on center and radius
    for (int i = 0; i < n; ++i) {
        float angle = 2 * PI * i / n;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        vertices.emplace_back(x, y);
    }

    return vertices;
}
/**/
void Polygon::updateVertices(const Point& delta) {
    for (int i = 0; i < vertexCount; i++){
        vertices[i] = vertices[i] + delta;
    }
}

RegularPolygon::RegularPolygon(const Point &center,int n, float length): Polygon(calculateRegularPolygon(
                                                                        center,n,length)), 
                                                                        center(center), EdgeCount(n),
                                                                        edgeLength(length) {}

//transform vector<Point> into float*, for al_draw_polygon
float* vectorToFloatArray(const std::vector<Point>& points) {
    float* result = new float[points.size() * 2]; 
    for (size_t i = 0; i < points.size(); ++i) {
        result[i * 2] = points[i].x;
        result[i * 2 + 1] = points[i].y;
    }
    return result;
} //REMEMBER TO DELETE FLOAT* AFTER USE