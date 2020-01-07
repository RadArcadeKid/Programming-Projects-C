#include "pieceicon.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <string>
//JAKE HENSON - HW5

/**
  Creates a new Piece object with coordinates x and y
  @param x int x coordinate
  @param y int y coordinate
  @param name - the name of what this PieceIcon is
*/
PieceIcon::PieceIcon(const int x, const int y, std::string name){
  name_ = name; //sets the color of the piece
  x_ = x; //x position will be the same as the BoardCell it's placed into
  y_ = y; //y position will be the same as the BoardCell it's placed into
}

QRectF PieceIcon::boundingRect() const
{
    return QRectF(x_, y_, width_height_, width_height_);
}

QPainterPath PieceIcon::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_height_, width_height_);
    return path;
}


void PieceIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QBrush b = painter->brush();

    if(name_ == "neutral"){
        color_ = QColor(89, 89, 89); //set the piece to gray
        painter->setBrush(QBrush(color_));
        painter->drawEllipse(QRect(this->x_, this->y_, this->width_height_, this->width_height_));
        painter->setBrush(b);
    }
    if(name_ == "converter"){
        painter->setBrush(QBrush(QColor(200, 200, 200))); //set the brush to netural color
        painter->drawEllipse(QRect(this->x_, this->y_, this->width_height_, this->width_height_));
        painter->setBrush(b);

        painter->setPen(QPen(QColor(0, 255, 238), 3));
        painter->drawLine(this->x_+5, this->y_+23, this->x_+width_height_-5, this->y_+23);
        painter->drawLine(this->x_+5, this->y_+23, this->x_+25, this->y_+35);
        painter->drawLine(this->x_+25, this->y_+35, this->x_+width_height_-5, this->y_+23);
    }
}

void PieceIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit PieceSelected(this); //emit the pieceSelected signal!
    //this will let the MainWindow know when it's pressed, and allow the player to use this powoerup
}
