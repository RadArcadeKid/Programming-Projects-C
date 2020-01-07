//JAKE HENSON
#include <iostream>
#include "Point.h"

/*
Main is designed to test the various things I programmed...
*/
int main(){
    //create three different point objects
    Point p1(5, 6);
    Point p2(1, 4);
    Point p3(24, 7);

    //display the three created points to the user
    std::cout << "Created three point objects, (x, y): " << std::endl << std::endl;
    std::cout << "  -- p1 = (" << p1.getX() << ", " << p1.getY() << ")" << std::endl;
    std::cout << "  -- p2 = (" << p2.getX() << ", " << p2.getY() << ")" << std::endl;
    std::cout << "  -- p3 = (" << p3.getX() << ", " << p3.getY() << ")" << std::endl << std::endl;


    //calculate and display the distance bettween them
    std::cout << "The distance between p1 and p2 is: " << p1.Distance(p2) << std::endl;
    std::cout << "The distance between p2 and p3 is: " << p2.Distance(p3) << std::endl;
    std::cout << "The distance between p3 and p1 is: " << p3.Distance(p1) << std::endl  << std::endl;

    //translate one of the points, display the input to the user
    std::cout << "Translating p1 by 15" << std::endl;
    p1.Translate(15);
    std::cout << "p1's new coordinates are: (" << p1.getX() << ", " << p1.getY() << ")" << std::endl;

    //calculate and display the new distance bettween them
    std::cout << "The new distance between p1 and p2 is: " << p1.Distance(p2) << std::endl;
    std::cout << "The new distance between p2 and p3 is: " << p2.Distance(p3) << std::endl;
    std::cout << "The new distance between p3 and p1 is: " << p3.Distance(p1) << std::endl  << std::endl;

    //translate one of the points by a negative amount, display the input to the user
    std::cout << "Translating p1 by -12" << std::endl;
    p1.Translate(-12);
    std::cout << "p1's new coordinates are: (" << p1.getX() << ", " << p1.getY() << ")" << std::endl;

    //calculate and display the new distance bettween them
    std::cout << "The new distance between p1 and p2 is: " << p1.Distance(p2) << std::endl;
    std::cout << "The new distance between p2 and p3 is: " << p2.Distance(p3) << std::endl;
    std::cout << "The new distance between p3 and p1 is: " << p3.Distance(p1) << std::endl  << std::endl;


    return 0;
}
