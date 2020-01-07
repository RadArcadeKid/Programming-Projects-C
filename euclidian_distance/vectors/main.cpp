//JAKE HENSON 
#include <iostream>
#include <vector>
#include "Point.h"

/*
Main is designed to test the various things I programmed...
*/
int main(){
    //create 3 different vectors to pass into point objects
    std::vector<int> v1{0, 1, 2, 3, 4};
    std::vector<int> v2{5, 2, 13, 34, 7};
    std::vector<int> v3{3, 7, 7, 55, 6};

    //create three different point objects NOW WITH VECTORS!
    Point p1( v1 );
    Point p2( v2 );
    Point p3( v3 );

    //display the three created points to the user
    std::cout << "Created three point objects with n dimensions, (n, n, n....): " << std::endl;
    std::cout << "  -- p1 = (";
    for(unsigned int i = 0; i < p1.vec.size(); i++){
        std::cout<< p1.getV(i);
        if(i < p1.vec.size() - 1) { //just for printing syntax
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;

    std::cout << "  -- p2 = (";
    for(unsigned int i = 0; i < p2.vec.size(); i++){
        std::cout<< p2.getV(i);
        if(i < p2.vec.size() - 1) { //just for printing syntax
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;

    std::cout << "  -- p3 = (";
    for(unsigned int i = 0; i < p3.vec.size(); i++){
        std::cout << p3.getV(i);
        if(i < p3.vec.size() - 1) { //just for printing syntax
            std::cout << ", ";
        }

    }
    std::cout << ")" << std::endl;

    //calculate and display the distance bettween them
    std::cout << "The distance between p1 and p2 is: " << p1.Distance(p2) << std::endl;
    std::cout << "The distance between p2 and p3 is: " << p2.Distance(p3) << std::endl;
    std::cout << "The distance between p3 and p1 is: " << p3.Distance(p1) << std::endl  << std::endl;

    //translate one of the points, display the input to the user
    std::cout << "Translating all values in p1 by 15..." << std::endl;
    p1.Translate(15);
    std::cout << "p1's new coordinates are: (";
    for(unsigned int i = 0; i < p1.vec.size(); i++){
        std::cout<< p1.getV(i);
        if(i < p1.vec.size() - 1) { //just for printing syntax
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;

    //calculate and display the new distance bettween them
    std::cout << "The new distance between p1 and p2 is: " << p1.Distance(p2) << std::endl;
    std::cout << "The new distance between p2 and p3 is: " << p2.Distance(p3) << std::endl;
    std::cout << "The new distance between p3 and p1 is: " << p3.Distance(p1) << std::endl  << std::endl;

    //translate one of the points by a negative amount, display the input to the user
    std::cout << "Translating all values in p1 by -12..." << std::endl;
    p1.Translate(-12);
    std::cout << "p1's new coordinates are: (";
    for(unsigned int i = 0; i < p1.vec.size(); i++){
        std::cout<< p1.getV(i);
        if(i < p1.vec.size() - 1) { //just for printing syntax
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;

    //calculate and display the new distance bettween them
    std::cout << "The new distance between p1 and p2 is: " << p1.Distance(p2) << std::endl;
    std::cout << "The new distance between p2 and p3 is: " << p2.Distance(p3) << std::endl;
    std::cout << "The new distance between p3 and p1 is: " << p3.Distance(p1) << std::endl  << std::endl;

    //change one of the points using setV(), display input
    std::cout << "Changing a single value in p2 using setter, value at index 3 (4th value) to 55..." << std::endl;
    p2.setV(3, 55);
    std::cout << "p2's new coordinates are: (";
    for(unsigned int i = 0; i < p2.vec.size(); i++){
        std::cout<< p2.getV(i);
        if(i < p2.vec.size() - 1) { //just for printing syntax
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;
    std::cout << std::endl;

    return 0;
}
