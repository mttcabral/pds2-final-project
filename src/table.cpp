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

Cell::Cell(Rectangle rectangle, string text) : rectangle(rectangle), text(text) {};

Cell::Cell() {
    this->rectangle = Rectangle();
    this->text = "";
}

Cell& Cell::operator = (const Cell& otherCell) {
    this->rectangle = otherCell.rectangle;
    this->text = otherCell.text;
    return *this;
}

void Cell::display(){
    cout << "Text: " << this->text << endl;
    cout << "Rectangle: "<< endl;
    this->rectangle.display();
    cout<<endl;
}

Row::Row() : textColor(Color()), rowColor(Color()) {
    column.resize(4);
    for(int i = 0; i < 4; i++)
        column[i] = new Cell();
}

Row::Row(Color textColor, Color rowColor) : textColor(textColor), rowColor(rowColor) {
    column.resize(4);
    for(int i = 0; i < 4; i++) {
        column[i] = new Cell();
    }
};

Row::~Row() {
    for(int i = 0; i < 4; i++)
        delete column[i];
    column.clear();
}

void Row::display(){
    for (int i = 0; i < 4; i++){
        this->column[i]->display();
    }
}

Table::Table(int numberRows, Rectangle inPlan) : numberRows(numberRows), plan(inPlan) {
    row.resize(9);

    Point firstCellTopLeft = inPlan.center + Point(((float) -inPlan.length)/(2.0), ((float) -inPlan.height)/(2.0)); // first Cell top left point
    float CellLength = ((float)inPlan.length)/(4.0);
    float CellHeight = ((float)inPlan.height)/((float)(numberRows+1));
    Point firstCellBottomRight = firstCellTopLeft + Point(CellLength, CellHeight); // first Cell bottom right point

    for (int i = 0; i < numberRows+1; i++){
        Point CellTopLeft = firstCellTopLeft + Point(0, i*CellHeight);
        Point CellBottomRight = firstCellBottomRight + Point(0, i*CellHeight);
        for (int j = 0; j < 4; j++) {
            if (j == 0) { // the first must fit the corner
                CellTopLeft = CellTopLeft;
                CellBottomRight = CellBottomRight;
                row[i].column[j]->rectangle = Rectangle(CellTopLeft, CellBottomRight);
            }
            else {
                CellTopLeft = CellTopLeft + Point(CellLength, 0);
                CellBottomRight = CellBottomRight + Point(CellLength, 0);;
                row[i].column[j]->rectangle = Rectangle(CellTopLeft, CellBottomRight);
            }
        }
    }
    row[0].column[0]->text = "RANK";
    row[0].column[1]->text = "NICKNAME";
    row[0].column[2]->text = "MAX PIPERS";
    row[0].column[3]->text = "PLAYS";
}

void Table::display() {
    for (int i = 0; i < numberRows; i++){
        row[i].display();
    }
}