#include "table.hpp"

Point::Point() : Point(0,0) {};

Point::Point(const Point& otherPoint) {
    this->x = otherPoint.x;
    this->y = otherPoint.y;
}

Point::Point(float x, float y) : x(x), y(y) {};

Point& Point::operator = (const Point& otherPoint) {
    if (this != &otherPoint) {
        this->x = otherPoint.x;
        this->y = otherPoint.y;
    }

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

Point Point::operator * (float f) {
    return Point((this->x)*f, (this->y)*f);
}

void Point::display() {
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

void Color::display(){
    cout<< "RGB: (" << this->r << "," << this->g << "," << this->b << ")" << endl;
}

Rectangle::Rectangle() : Rectangle(Point(0.0, 0.0), 0.0, 0.0) {};

Rectangle::Rectangle(Point center, float length, float height) : center(center), length(length), height(height) {
    this->topLeft = center + Point(((float) -length)/(2.0), ((float) -height)/(2.0));
    this->bottomRight = center + Point(length/(2.0), height/(2.0));
}

Rectangle::Rectangle(Point topLeft, Point bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {
    this->center = (topLeft + bottomRight)/(2.0);
    this->length = (bottomRight.x - topLeft.x);
    this->height = (bottomRight.y - topLeft.y);
}

Rectangle::Rectangle(const Rectangle& otherRectangle) {
    this->topLeft = otherRectangle.topLeft;
    this->center = otherRectangle.center;
    this->bottomRight = otherRectangle.bottomRight;
    this->length = otherRectangle.length;
    this->height = otherRectangle.height;
}

Rectangle& Rectangle::operator = (const Rectangle& otherRectangle) {
    if (this != &otherRectangle) {
        this->topLeft = otherRectangle.topLeft;
        this->bottomRight = otherRectangle.bottomRight;
        this->center = otherRectangle.center;
        this->length = otherRectangle.length;
        this->height = otherRectangle.height;
    }

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

Cell::Cell(Rectangle cellRectangle, string text) : cellRectangle(cellRectangle), text(text) {};

Cell::Cell(Rectangle cellRectangle) : cellRectangle(cellRectangle), text("") {};

Cell::Cell() {
    this->cellRectangle = Rectangle();
    this->text = "";
}

Cell::Cell(const Cell& otherCell) {
    this->cellRectangle = otherCell.cellRectangle;
    this->text = otherCell.text;
}

Cell& Cell::operator = (const Cell& otherCell) {
    this->cellRectangle = otherCell.cellRectangle;
    this->text = otherCell.text;

    return *this;
}

void Cell::display(){
    cout << "Text: " << this->text << endl;
    cout << "Rectangle: "<< endl;
    this->cellRectangle.display();
    cout<<endl;
}

Row::Row(const Row& otherRow) :
rowRectangle(otherRow.rowRectangle),
textColor(otherRow.textColor),
rowColor(otherRow.rowColor),
column(otherRow.column) {};

Row::Row() : Row(Color(), Color()) {};

Row::Row(Color textColor, Color rowColor) : rowRectangle(Rectangle()), textColor(textColor), rowColor(rowColor) {
    column.resize(NUMCOLUMNS);
    for(int i = 0; i < NUMCOLUMNS; i++) {
        column[i] = Cell();
    }
};

Row::Row(Point rowTopLeft, Point rowBottomRight) : rowRectangle(Rectangle(rowTopLeft, rowBottomRight)) {};

Row::Row(Rectangle inRowRectangle) : rowRectangle(inRowRectangle), textColor(Color()), rowColor(Color()) {
    float cellLength = inRowRectangle.length/((float) NUMCOLUMNS);
    float cellHeight = inRowRectangle.height;
    Point firstCellTopLeft = inRowRectangle.topLeft;
    Point firstCellBottomRight = inRowRectangle.topLeft + Point(cellLength, cellHeight);

    column.resize(NUMCOLUMNS);
    for(int i = 0; i < NUMCOLUMNS; i++) {
        Rectangle tempCellRectangle = Rectangle(firstCellTopLeft + Point(i*cellLength, 0), firstCellBottomRight + Point(i*cellLength, 0));
        column[i] = Cell(tempCellRectangle);
    }
}

Row& Row::operator = (const Row& otherRow) {
    if (this != &otherRow) {
        this->rowRectangle = otherRow.rowRectangle;
        this->textColor = otherRow.textColor;

        column.resize(NUMCOLUMNS);
        for(int i = 0; i < NUMCOLUMNS; i++)
            column[i] = Cell(otherRow.column[i]);
    }

    /*this->rowRectangle = otherRow.rowRectangle;
    this->textColor = otherRow.rowColor;
    this->textColor = otherRow.textColor;*/

    return *this;
}


void Row::display(){
    for (int i = 0; i < NUMCOLUMNS; i++){
        this->column[i].display();
    }
}

Table::Table(Rectangle inTableRectangle) : tableRectangle(inTableRectangle) {
    row.resize(NUMROWS);

    Point firstRowTopLeft = inTableRectangle.topLeft; // first Cell top left point
    float rowLength = inTableRectangle.length;
    float rowHeight = inTableRectangle.height/((float) (NUMROWS));
    Point firstCellBottomRight = firstRowTopLeft + Point(rowLength, rowHeight); // first Cell bottom right point

    for (int i = 0; i < NUMROWS; i++){
        Point rowTopLeft = firstRowTopLeft + Point(0, i*rowHeight);
        Point rowBottomRight = firstCellBottomRight + Point(0, i*rowHeight);
        row[i] = Row(Rectangle(rowTopLeft, rowBottomRight));
    }

    row[0].column[0].text = "RANK";
    row[0].column[1].text = "NICKNAME";
    row[0].column[2].text = "MAX PIPERS";
    row[0].column[3].text = "PLAYS";
}

Table::Table(const Table& otherTable) {
    this->tableRectangle = otherTable.tableRectangle;
    for (int i = 0; i < NUMROWS; i ++) {
        for (int j = 0; j < NUMCOLUMNS; j++)
            this->row[i].column[j] = otherTable.row[i].column[j];
    }
}

Table& Table::operator = (const Table& otherTable) {
    if (this != &otherTable) {
        this->tableRectangle = otherTable.tableRectangle;
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