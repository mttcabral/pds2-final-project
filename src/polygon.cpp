#include "polygon.hpp"

using namespace std;

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

vector<Point> calculateRectangle(const Point &center, float w, float h) {
    Point aux1(w/2,h/2);
    Point aux2(w/2,-h/2);
    return {center - aux1, center + aux1, 
            center - aux2, center + aux2};
}