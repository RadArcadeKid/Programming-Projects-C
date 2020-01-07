#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include "bar.h"
//JAKE HENSON - HW5

/**
 * @brief Bar::Bar - Used for the bargraph in MainWindow
 * @param x
 * @param player
 */
Bar::Bar(const int x, int player){
    if(player == 1)this->color_ = color_ = QColor(0, 255, 238);
    else if(player == 2) this->color_ = QColor(255, 79, 229);

    this->x_ = x;

    setHeight(0); //by default, this'll be set to zero cause neither player has won any games
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
 * @brief Bar::setHeight - Sets the height of the bar based on the number of wins
 * @param numWins - the number of wins for this player (graph)
 */
void Bar::setHeight(int numWins){
    this->y_ = (350 - (35 * numWins)); //to allign the bar at the bottom
    this->height_ = (35 * numWins); //0 = 0, 1 = 35, 2 = 70, etc.
}

