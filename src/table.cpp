#include "table.hpp"

Point::Point() : Point(0,0) {};

Point::Point(const Point& otherPoint) {
    this->x = otherPoint.x;
    this->y = otherPoint.y;
}

Point::Point(float x, float y) : x(x), y(y) {};

Point& Point::operator = (const Point& otherPoint) {
    this->x = otherPoint.x;
    this->y = otherPoint.y;
    return *this;
}

Point Point::operator - (const Point& otherPoint) const {
    return Point(this->x - otherPoint.x, this->y - otherPoint.y);
}
    
Point Point::operator + (const Point& otherPoint) const {
    return Point(this->x + otherPoint.x, this->y + otherPoint.y);
}

Point Point::operator / (float f) const {
    return Point((this->x)/f, (this->y)/f);
}

void Point::display() {
    cout<<"(" << this->x << "," << this->y << ")" << endl;
}