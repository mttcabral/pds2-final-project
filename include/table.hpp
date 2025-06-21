#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <stdbool.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

const int NUMCOLUMNS = 4;
const int NUMROWS = 9;

struct Point {
    float x, y;

    Point();
    Point(float, float);
    Point(const Point&);


    Point& operator = (const Point&);
    Point operator - (const Point&) const;
    Point operator + (const Point&) const;
    Point operator / (float) const;
    Point operator * (float);

    void display();
};

struct Color{
    float r, g, b;

    Color();
    Color(float, float, float);
    Color(const Color&);

    Color& operator = (const Color&);

    void display();
};

struct Rectangle {
    Point center, topLeft, bottomRight;
    float length, height;

    Rectangle();
    Rectangle(Point, float, float);
    Rectangle(Point, Point);
    Rectangle(const Rectangle&);

    Rectangle& operator = (const Rectangle&);

    void display();
};

struct Cell {
    Rectangle cellRectangle;
    string text;

    Cell();
    Cell(Rectangle, string);
    Cell(Rectangle);
    Cell(const Cell&);

    Cell& operator = (const Cell&);

    void display();
};

struct Row {
    vector<Cell> column;
    Rectangle rowRectangle;
    Color textColor, rowColor;

    Row();
    Row(Color, Color);
    Row(Rectangle);
    Row(Point, Point);
    Row(const Row&);

    Row& operator = (const Row&);

    void display();
};

struct Table {
    Rectangle tableRectangle;
    vector<Row> row;

    Table(Rectangle);
    Table(const Table&);

    Table& operator = (const Table&);

    //void updateNumberRows(int);
    void display();
};

#endif