#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <stdbool.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

const int NUMCOLUMNS = 4;
const int NUMROWS = 9;

struct PointT {
    private:
        float toZero(float);

    public:
        float x, y;

        PointT();
        PointT(float, float);
        PointT(const PointT&);


        PointT& operator = (const PointT&);
        PointT operator - (const PointT&) const;
        PointT operator + (const PointT&) const;
        PointT operator / (float) const;
        PointT operator * (float);

        void display();
};

struct Color{
    float r, g, b; // 0 - 255

    Color();
    Color(float, float, float);
    Color(const Color&);

    Color& operator = (const Color&);
    Color operator / (float) const;

    void display();
};

struct RectangleT {
    PointT center, topLeft, bottomRight;
    vector<PointT> subCenters;
    float length, height;

    RectangleT();
    RectangleT(PointT, float, float);
    RectangleT(PointT, PointT);
    RectangleT(const RectangleT&);

    RectangleT& operator = (const RectangleT&);

    void display();
};

struct Row {
    RectangleT rowRectangle;
    vector<string> texts;
    Color textColor, rowColor;

    Row();
    Row(Color, Color, RectangleT);
    Row(RectangleT);
    Row(PointT, PointT);
    Row(const Row&);

    Row& operator = (const Row&);

    void display();
};

struct Table {
    RectangleT tableRectangle;
    vector<Row> row;

    Table();
    Table(RectangleT);
    Table(const Table&);

    Table& operator = (const Table&);

    //void updateNumberRows(int);
    void display();
};

#endif
