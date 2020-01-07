//JAKE HENSON

#ifndef _POINT_H_  // header guard
#define _POINT_H_

//Class definition
class Point{
  private:
   int x; //coordinate for x value later
   int y; //coordinate for y value later

  public:
    Point(int x_, int y_); //constructor

    void setX(int u); //setters + getters
    void setY(int v);
    int getX();
    int getY();

    void Translate(int val);  //math methods
    double Distance(Point point2);
};

#endif
