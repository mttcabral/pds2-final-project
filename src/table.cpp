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

Color::Color() : Color(0, 0, 0) {};
Color::Color(float r, float g, float b) : r(r), g(g), b(b) {};

void Color::display(){
    cout<< "RGB: (" << this->r << "," << this->g << "," << this->b << ")" << endl;
}

Rectangle::Rectangle() : Rectangle(Point(0.0, 0.0), 0.0, 0.0) {};
Rectangle::Rectangle(Point center, float length, float height) : center(center), length(length), height(height) {
    this->topLeft = center + Point(((float) -length)/(2.0), ((float) -height)/(2.0));
    this->bottomRight = center + Point(length/2, height/2);
}

Rectangle::Rectangle(Point topLeft, Point bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {
    this->center = (topLeft + bottomRight)/(2.0);
    this->length = (bottomRight.x - topLeft.x);
    this->height = (bottomRight.y - topLeft.y);
}

Rectangle& Rectangle::operator = (const Rectangle& otherRectangle) {
    this->topLeft = otherRectangle.topLeft;
    this->bottomRight = otherRectangle.bottomRight;
    this->center = otherRectangle.center;
    this->length = otherRectangle.length;
    this->height = otherRectangle.height;
    return *this;
}

void Rectangle::display(){
    cout<<"Top Left: ";
    this->topLeft.display();
    cout<<"Center: ";
    this->center.display();
    cout<<"Bottom Right: ";
    this->bottomRight.display();
    cout<<endl;
}