//JAKE HENSON 
#include <iostream>
#include "Point.h"
#include <math.h>

//Constructor for point
Point::Point(int x_, int y_){
    setX(x_);
    setY(y_);  //call the setter functions to easily initialize the object
}

//Setter for X
void Point::setX(int u){
    y = u;
}

//Setter for Y
void Point::setY(int v){
    x = v;
}

//Getter for X
int Point::getX(){
    return x;
}

//Getter for Y
int Point::getY(){
    return y;
}

//Translate -- this moves all of Point's coordinates by whatever integer value is passed to the method
void Point::Translate(int val){
    x += val;
    y += val;
}

//Calculate the euclidian distance between this Point and another
double Point::Distance(Point point2){
    int xdis = (x - point2.getX()); //(x2-x1) - for initial calculation of the xdistance
    int ydis = (y - point2.getY());   //(y2-y1) - for intiial calculation of the ydistance
    double result = sqrt( (xdis * xdis) + (ydis * ydis) );
    return result; //return the square root of ((x2-x1)^2 + (y2-y1)^2), i.e. Euclidian distance bettween the two points
}
