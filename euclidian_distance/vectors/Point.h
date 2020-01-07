//JAKE HENSON 
#include <vector>

#ifndef _POINT_H_  // header guard
#define _POINT_H_

//Class definition
class Point{
  public:
    std::vector<int> vec; //vector (I kept getting issues making this private instead of public)

    //constructor
    Point(std::vector<int> vec);

    //setters + getters
    void setV(int i, int newVal);
    int getV(int n);

    //math methods
    void Translate(int val);
    double Distance(Point point2);
};

#endif
