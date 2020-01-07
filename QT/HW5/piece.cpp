#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <string>
#include "piece.h"
//JAKE HENSON - HW5

/**
  Creates a new Piece object with coordinates x and y
  @param x int x coordinate
  @param y int y coordinate
*/
Piece::Piece(const int x, const int y, std::string name){
  setPieceIdentity(name); //sets the color of the piece
  x_ = x; //x position will be the same as the BoardCell it's placed into
  y_ = y; //y position will be the same as the BoardCell it's placed into
}

QRectF Piece::boundingRect() const
{
    return QRectF(x_, y_, width_height_, width_height_);
}

QPainterPath Piece::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_height_, width_height_);
    return path;
}

std::string Piece::getPieceName(){
    std::string blue = "blue";
    std::string pink = "pink"; //I have to set these up here because QT was getting angry at just returning the strings
    std::string neutral = "neutral"; //I have to set these up here because QT was getting angry at just returning the strings


    if(color_ == QColor(0, 255, 238)) return blue;
    if(color_ == QColor(255, 79, 229)) return pink;
    if(color_ == QColor(89, 89, 89)) return neutral;

}

void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawEllipse(QRect(this->x_+43, this->y_+77, this->width_height_, this->width_height_));
    //the reason that this is +40 and +70 is so that the cells will draw at the right spot instead of the top left corner
    //before, we'd just change the scene view, but I need that for other parts of the game, so they're changed *where* they're drawn instead
    painter->setBrush(b);
}

/**
 * @brief Piece::setPieceIdentity - Sets the color of the piece based on its name
 * @param name - the name of the piece
 * @return none
 */
void Piece::setPieceIdentity(std::string name){
    if(name == "blue"){
        color_ = QColor(0, 255, 238);
    }
    if(name == "pink"){
        color_ = QColor(255, 79, 229);
    }
    if(name == "neutral"){
        color_ = QColor(89, 89, 89);
    }
}


////////////////////////////////////////////////////////////////////
/// For the INHERITED ConvertPowerup piece!!! (Contained within the same file for simplicities' sake)
////////////////////////////////////////////////////////////////////
void ConvertPowerup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget)

    QBrush b = painter->brush();
    painter->setBrush(QBrush(QColor(200, 200, 200)));
    painter->drawEllipse(QRect(this->real_x_+43, this->real_y_+77, this->width_height_, this->width_height_));
//    painter->drawEllipse(QRect(this->real_x_, this->real_y_, this->width_height_, this->width_height_));

    if(player_ == 1){
        painter->setPen(QPen(QColor(0, 255, 238), 3));
    }
    else if(player_ == 2){
        painter->setPen(QPen(QColor(255, 79, 229), 3));
    }

//    painter->drawLine(this->real_x_+55, this->real_y_+125, this->real_x_+width_height_+32, this->real_y_+125);
//    painter->drawLine(this->real_x_+55, this->real_y_+125, this->real_x_+width_height_, this->real_y_+100);
//    painter->drawLine(this->real_x_+width_height_, this->real_y_+100, this->real_x_+width_height_+32, this->real_y_+125);
    painter->drawLine(this->real_x_+55, this->real_y_+110, this->real_x_+width_height_+32, this->real_y_+110);
    painter->drawLine(this->real_x_+55, this->real_y_+110, this->real_x_+width_height_, this->real_y_+135);
    painter->drawLine(this->real_x_+width_height_, this->real_y_+135, this->real_x_+width_height_+32, this->real_y_+110);

    painter->setBrush(b);

}
