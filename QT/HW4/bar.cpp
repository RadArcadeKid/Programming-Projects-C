#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "bar.h"
//JAKE HENSON - HW4
//bar.cpp
//An object for each bar on the graph, holds a color and x and y coodinate
//Called by PlotWindow

Bar::Bar(const int x, const int height, QColor color) {
  this->color_ =  color;
  this->x_ = x;
  this->y_ = (100 - height) + 300; //to allign the bar at the bottom
  this->height_ = height; //convert height to a negative value so the graph draws up instead of down

}

QRectF Bar::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath Bar::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_); //add a rectangle, not an oval like in Point
    return path;
}

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(x_, y_, this->width_, this->height_));
    painter->setBrush(b);
}

/**
 * Moves the bar's current position back 25 (the width of the cell)
 * Used during the movement of the graph
 * @param - none
 * @return - none
 */
void Bar::moveback(){
    this->x_ -= 25;
    if(this->x_<0) this->x_ = 0; //make sure it won't draw on negative space
}
