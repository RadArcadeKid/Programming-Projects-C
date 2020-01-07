#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include "boardcell.h"
//JAKE HENSON - HW5

/**
  Creates a new BoardCell object with coordinates x and y
  @param x int x coordinate
  @param y int y coordinate
*/
BoardCell::BoardCell(const int x, const int y) {
  QColor white(255,255,255); //just plain white!
  this->color_ = white;
  x_ = x  * 90; //x90 because the dimensions of the board are shifted
  y_ = y  * 90;

  thisPiece_ = nullptr;
  thisPowerup_ = nullptr;
}

QRectF BoardCell::boundingRect() const
{
    return QRectF(x_, y_, width_height_, width_height_);
}

QPainterPath BoardCell::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_height_, width_height_);
    return path;
}

void BoardCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));
    painter->setPen(QPen(Qt::black, 2));


    painter->drawRect(QRect(this->x_+40, this->y_+75, this->width_height_, this->width_height_));
    //the reason that this is +40 ansd +70 is so that the cells will draw at the right spot instead of the top left corner
    //before, we'd just change the scene view, but I need that for other parts of the game, so they're changed *where* they're drawn instead
    painter->setBrush(b);
}

/**
 * @brief BoardCell::setPiece -- Sets the desired piece inside the BoardCell object
 * @param takes in the piecename
 * @returns none
 */
void BoardCell::setPiece(std::string piecename){
    if(this->thisPiece_ != nullptr){
        this->thisPiece_ = nullptr; //empty the piece if there's one already there
    }
    if(piecename == "empty"){ //if we're resetting this back to empty
        this->thisPiece_ = nullptr; //empty the piece
        this->color_ = Qt::white;
        delete thisPiece_;
    }
    else{ //otherwise...
        this->thisPiece_ = new Piece(x_, y_, piecename); //sets this BoardCell's piece based on piecename!
    }
}


/**
 * @brief OVERLOADED BoardCell::setPiece -- Sets the desired POWERUP inside the BoardCell object
 * @param takes in the piecename and the player!
 * @returns none
 */
void BoardCell::setPiece(std::string piecename, int player){
        this->thisPowerup_ = new ConvertPowerup(x_, y_, player); //create a new converter piece
        this->thisPiece_ = nullptr; //even though this piece will
}

/**
 * @brief BoardCell::RepaintThisCell - Used for when the player wins the game, to repaint the boardcell to GREEN
 */
void BoardCell::RepaintThisCell(){
    this->color_ = Qt::green;
}
