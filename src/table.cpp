#include "table.hpp"
// NUMCOLUMNS
// criar funcao que coloca titulos no Leaderboard

float PointT::toZero(float smallNumber) {
    if(abs(smallNumber) < 1e-5)
        return 0.0;
    return smallNumber;
}

PointT::PointT() : PointT(0,1) {};

PointT::PointT(const PointT& otherPointT) {
    this->x = otherPointT.x;
    this->y = otherPointT.y;
}

PointT::PointT(float x, float y) : x(toZero(x)), y(toZero(y)) {};

PointT& PointT::operator = (const PointT& otherPoint) {
    if (this != &otherPoint) {
        this->x = otherPoint.x;
        this->y = otherPoint.y;
    }

    return *this;
}

PointT PointT::operator - (const PointT& otherPoint) const {
    return PointT(this->x - otherPoint.x, this->y - otherPoint.y);
}
    
PointT PointT::operator + (const PointT& otherPoint) const {
    return PointT(this->x + otherPoint.x, this->y + otherPoint.y);
}

PointT PointT::operator / (float f) const {
    return PointT((this->x)/f, (this->y)/f);
}

PointT PointT::operator * (float f) {
    return PointT((this->x)*f, (this->y)*f);
}

void PointT::display() {
    cout<<"(" << this->x << "," << this->y << ")" << endl;
}

Color::Color() : Color(0, 0, 0) {};

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {};

Color::Color(const Color& otherColor) {
    this->r = otherColor.r;
    this->g = otherColor.g;
    this->b = otherColor.b;
}

Color& Color::operator = (const Color& otherColor) {
    if (this != &otherColor){
        this->r = otherColor.r;
        this->g = otherColor.g;
        this->b = otherColor.b;
    }
    return *this;
}

Color Color::operator / (float f) const {
    return Color((this->r)/f, (this->g)/f, (this->b)/f);
}

void Color::display(){
    cout<< "RGB: (" << this->r << "," << this->g << "," << this->b << ")" << endl;
}

RectangleT::RectangleT() : RectangleT(PointT(0.0, 0.0), 0.0, 0.0) {};

RectangleT::RectangleT(PointT center, float length, float height) : center(center), length(length), height(height) {
    this->topLeft = center + PointT(((float) -length)/(2.0), ((float) -height)/(2.0));
    this->bottomRight = center + PointT(length/(2.0), height/(2.0));

    float subLength = length/(NUMCOLUMNS);
    float subHeight = height/(2.0);
    PointT firstSubCenter = topLeft + PointT(subLength/(2.0), subHeight);

    this->subCenters.resize(NUMCOLUMNS);
    for(int i = 0; i < NUMCOLUMNS; i++)
        subCenters[i] = firstSubCenter + PointT(i*subLength, 0);
}

RectangleT::RectangleT(PointT topLeft, PointT bottomRight) : topLeft(topLeft), bottomRight(bottomRight){
    this->center = (topLeft + bottomRight)/(2.0);
    this->length = (bottomRight.x - topLeft.x);
    this->height = (bottomRight.y - topLeft.y);

    float subLength = length/(NUMCOLUMNS);
    float subHeight = height/(2.0);
    PointT firstSubCenter = topLeft + PointT(subLength/(2.0), subHeight);

    this->subCenters.resize(NUMCOLUMNS);
    for(int i = 0; i < NUMCOLUMNS; i++)
        subCenters[i] = firstSubCenter + PointT(i*subLength, 0);
}

RectangleT::RectangleT(const RectangleT& otherRectangle) {
    this->topLeft = otherRectangle.topLeft;
    this->center = otherRectangle.center;
    this->bottomRight = otherRectangle.bottomRight;
    this->length = otherRectangle.length;
    this->height = otherRectangle.height;

    this->subCenters.resize(NUMCOLUMNS);
    for(int i = 0; i < NUMCOLUMNS; i++)
        subCenters[i] = otherRectangle.subCenters[i];
}

RectangleT& RectangleT::operator = (const RectangleT& otherRectangle) {
    if (this != &otherRectangle) {
        this->topLeft = otherRectangle.topLeft;
        this->bottomRight = otherRectangle.bottomRight;
        this->center = otherRectangle.center;
        this->length = otherRectangle.length;
        this->height = otherRectangle.height;

        this->subCenters.resize(NUMCOLUMNS);
        for(int i = 0; i < NUMCOLUMNS; i++)
            subCenters[i] = otherRectangle.subCenters[i];
    }

    return *this;
}

void RectangleT::display(){
    cout<<"Top Left: ";
    this->topLeft.display();
    cout<<"Center: ";
    this->center.display();
    cout<<"Bottom Right: ";
    this->bottomRight.display();
    cout<<"Subcenters:\n";
    for(int i = 0; i < NUMCOLUMNS; i ++){
        this->subCenters[i].display();
        cout << " ";
    }

    cout<<endl;
}

Row::Row(const Row& otherRow) : rowRectangle(otherRow.rowRectangle), textColor(otherRow.textColor), rowColor(otherRow.rowColor) {
    texts.resize(NUMCOLUMNS);
    for(int i = 0; i < NUMCOLUMNS; i++)
        texts[i] = otherRow.texts[i];
};

Row::Row() : Row(Color(), Color(), RectangleT()) {};

Row::Row(PointT rowTopLeft, PointT rowBottomRight) : Row(Color(), Color(), RectangleT(rowTopLeft, rowBottomRight)) {};

Row::Row(RectangleT inRowRectangle) : Row(Color(), Color(), inRowRectangle) {};

Row::Row(Color textColor, Color rowColor, RectangleT inRowRectangle) : rowRectangle(inRowRectangle), textColor(textColor), rowColor(rowColor) {
    texts.resize(NUMCOLUMNS);
    for(int i = 0; i < NUMCOLUMNS; i++) 
        texts[i] = "";
}

Row& Row::operator = (const Row& otherRow) {
    if (this != &otherRow) {
        this->rowRectangle = otherRow.rowRectangle;
        this->textColor = otherRow.textColor;
        this->rowColor = otherRow.rowColor;

        texts.resize(NUMCOLUMNS);
        for(int i = 0; i < NUMCOLUMNS; i++)
            texts[i] = otherRow.texts[i];
    }

    return *this;
}


void Row::display(){
    cout << "Row Color: ";
    this->rowColor.display();
    cout << "Text Color: ";
    this->textColor.display();
    cout << endl;
    cout << "Texts: ";
    for (string text : this->texts)
        cout << text << " | ";
    cout << endl;
    this->rowRectangle.display();
}

Table::Table() : Table(RectangleT()) {};

Table::Table(RectangleT inTableRectangle) : tableRectangle(inTableRectangle) {
    row.resize(NUMROWS);

    PointT firstRowTopLeft = inTableRectangle.topLeft; // first Cell top left point
    float rowLength = inTableRectangle.length;
    float rowHeight = inTableRectangle.height/((float) (NUMROWS));
    PointT firstRowBottomRight = firstRowTopLeft + PointT(rowLength, rowHeight); // first Cell bottom right point
    
    for (int i = 0; i < NUMROWS; i++)
        row[i].rowRectangle = RectangleT(firstRowTopLeft + PointT(0, i*rowHeight), firstRowBottomRight + PointT(0, i*rowHeight));
    
}

Table::Table(const Table& otherTable) {
    this->tableRectangle = otherTable.tableRectangle;

    this->row.resize(NUMROWS); // to avoid segmentation fault
    for (int i = 0; i < NUMROWS; i ++) {
        this->row[i] = otherTable.row[i];
    }
}

Table& Table::operator = (const Table& otherTable) {
    if (this != &otherTable) {
        this->tableRectangle = otherTable.tableRectangle;

        this->row.resize(NUMROWS); // to avoid segmentation fault
        for (int i = 0; i < NUMROWS; i ++)
            this->row[i] = otherTable.row[i];
    }

    return *this;
}

void Table::display() {
    for (int i = 0; i < NUMROWS; i++){
        row[i].display();
    }
}