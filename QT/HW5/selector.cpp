#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include "selector.h"
//JAKE HENSON - HW5

/**
 * @brief Selector::Selector - The selector that appears at the top of the game
 * @param x - where it goin'
 */
Selector::Selector(int x) {
  this->color_ = Qt::white;
  x_ = (x * 90) + 40; //x90 because the dimensions of the board are shifted, 40 because
  y_ = 0;
  thisPiece_ = nullptr;

}

QRectF Selector::boundingRect() const
{
    return QRectF(x_, y_, this->height_, this->width_);
}

QPainterPath Selector::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, this->height_, this->width_);
    return path;
}

void Selector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    //painter->drawRect(QRect(this->x_, this->y_, this->height_, this->width_));

    //draw piece here!!!
    painter->setBrush(QBrush(piece_type_color_)); //set the piececolor here
    painter->drawEllipse(QRect(this->x_+23, this->y_+2, 45, 45));

    if(color_ ==  QColor(200, 200, 200)){ //if we're dealing with a converter piece, this must be drawn different!
            painter->setBrush(QBrush(QColor(200, 200, 200))); //set the brush to netural color
            painter->drawEllipse(QRect(this->x_, this->y_, 45, 45));
            painter->setBrush(b);

            painter->setPen(QPen(QColor(0, 255, 238), 2));
            painter->drawLine(this->x_+5, 23, this->x_+40, 23);
            painter->drawLine(this->x_+5, 23, this->x_+25, 35);
            painter->drawLine(this->x_+25, 35, this->x_+40, 23);
    }


    painter->setBrush(QBrush(color_)); //reset brush

    painter->setPen(QPen(Qt::black, 3));
    //draw the arrows to show where the player should drop the piece

    painter->drawLine(this->x_+35, this->width_-18, this->x_+45, this->width_-12);
    painter->drawLine(this->x_+45, this->width_-12, this->x_+55, this->width_-18);

    painter->drawLine(this->x_+35, this->width_-11, this->x_+45, this->width_-5);
    painter->drawLine(this->x_+45, this->width_-5, this->x_+55, this->width_-11);


    painter->setBrush(b);

}

/**
 * @brief Selector::MoveSelector - Moves the selector based on userinput from Mainwindow
 * @param col - which column to move the Selector to (column 0-6)
 */
void Selector::MoveSelector(int col){
    x_ = (col*90) + 40;
}

/**
 * @brief Selector::setPieceColor Sets the piece color of the selector based on name
 * @param name - the name of the piece to set the piececolor to!
 */
void Selector::setPieceColor(std::string name){
    name_ = name;

    if(name == "blue"){
        piece_type_color_ = QColor(0, 255, 238);
    }
    if(name == "pink"){
        piece_type_color_ = QColor(255, 79, 229);
    }
    if(name == "neutral"){
        piece_type_color_ = QColor(89, 89, 89);
    }
    if(name == "converter"){
        piece_type_color_ = QColor(200, 200, 200);
        //TODO: Finish the rest of the art for piececonverter so it's got the lil lines
    }
}
