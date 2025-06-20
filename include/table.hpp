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

struct Rectangle {
    Point center, topLeft, bottomRight;
    float length, height;

    Rectangle();
    Rectangle(Point, float, float);
    Rectangle(Point, Point);

    Rectangle& operator = (const Rectangle&);

    void display();
};

struct Cell {
    Rectangle rectangle;
    string text;

    Cell();
    Cell(Rectangle, string);

    Cell& operator = (const Cell&);

    void display();
};

struct Row {
    vector<Cell*> column;
    Color textColor, rowColor;

    Row();
    Row(Color, Color);
    ~Row();

    void display();
};

struct Table {
    int numberRows;
    Rectangle plan;
    vector<Row> row;

    Table(int, Rectangle);

    void display();
};

#endif