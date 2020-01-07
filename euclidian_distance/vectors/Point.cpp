//JAKE HENSON 
#include <iostream>
#include <vector>
#include <math.h>
#include <stdexcept>
#include "Point.h"


//Constructor for point
Point::Point(std::vector<int> vec_){
    vec = vec_;
}

//Setter for vector  - i is the vector at index i, newVal is the new value it's being set to
void Point::setV(int p, int newVal){
    vec[p] = newVal;
}

//Getter for vector, checks the element at n
int Point::getV(int n){
    return vec[n];
}

//Translate -- this moves all of Point's coordinates by whatever integer value is passed to the method
void Point::Translate(int val){
    for(unsigned int i=0; i < vec.size(); i++){
        vec[i] += val;
    }
}

//Calculate the euclidian distance between this Point and another for all elements
double Point::Distance(Point point2){
    double result = 0.0; //intialize result to 0 for now...stores each element squared in the euclidian distance formula later
    double tmp = 0.0; //temporary vector for storing the value of a single element of euclidian distance

    if(vec.size() != point2.vec.size()){ //check that both vextors have the same size
           throw std::invalid_argument("These two vector sizes are not the same. Try again"); //throw an error if they do
       }

    //loop to get the n element of each point and do the first set of calculations with them:
    //((n2-n1)^2 + (m2-m1)^2 + ...), i.e. Euclidian distance bettween n points
    for(unsigned int i = 0; i < vec.size(); i++){
        tmp = ((vec[i] - point2.vec[i]));
        result += (tmp * tmp); //same as squaring each portion of the distance forumla, e.g. (x2-x1)^2
    }

    return sqrt( result ); //return the square root of the final result (each element we calculated earlier);
}
