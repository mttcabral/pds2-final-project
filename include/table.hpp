#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <stdbool.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

struct Point {
    float x, y;

    Point();
    Point(float, float);
    Point(const Point&);


    Point& operator = (const Point&);
    Point operator - (const Point&) const;
    Point operator + (const Point&) const;
    Point operator / (float) const;

    void display();
};

struct Color{
    float r, g, b;

    Color();
    Color(float, float, float);

    void display();
};

#endif