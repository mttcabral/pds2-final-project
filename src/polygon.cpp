#include "polygon.hpp"


bool isColidingSAT(const Polygon &a, const Polygon &b) {
    
    std::set<Point> axes;

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