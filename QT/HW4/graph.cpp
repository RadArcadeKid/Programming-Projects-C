#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "graph.h"
#include "bar.h"
//JAKE HENSON - HW4
//Graph.cpp
//Just the barebones object for the graph
//Run + created using PlotWindow and UI

/**
 * Constructor
 * @param - none
 * @return - none
 */
Graph::Graph() {
  QColor defcolor(255, 255, 255); //the default white
  this->color_ =  defcolor;
}

QRectF Graph::boundingRect() const
{
    return QRectF(0, 300, width_, height_);
}

QPainterPath Graph::shape() const
{
    QPainterPath path;
    path.addRect(0, 300, width_, height_);
    return path;
}

void Graph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(0, 300, this->width_, this->height_));
    painter->setBrush(b);
}
