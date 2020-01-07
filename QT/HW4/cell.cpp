#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "cell.h"
//JAKE HENSON - HW4
//Cell.cpp
//An object for each cell on the grid, holds a color and x and y coodinate, as well as a clicked signal
//Based off of the Point objet from previous homeworks
//Called by PlotWindow

/**
  Creates a new Cell object with coordinates x and y
  @param x int x coordinate
  @param y int y coordinate
*/
Cell::Cell(const int x, const int y) {
  QColor defaultPink(255, 0, 255); //the default pink color, to be set later
  //this->color_ =  defaultPink;
  RandomInitialStatus(); //set the cell status on spawn

  SetColor(defaultPink); //set the cell color to the default pink, for now
  x_ = x;
  y_ = y;
}

QRectF Cell::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_); //add a rectangle, not an oval like in Point
    return path;
}

/**
 * Sets the cell status based on a random true/false using the isAlive_ variable!
 * (Should only be called once the cell is created)
 * @param - none
 * @return - none
 */
void Cell::RandomInitialStatus(){
    if((rand() % 2) == 1){ //randonly determine whether to set this cell to alive or dead once it gets initialized
        isAlive_ = true; //set the cell to alive or dead when it gets initialized using random!
    }
    else{
        isAlive_ =  false;
    }
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}

/**
  Sets the CURRENT Cell status to the requested one (useful for accessing elsewhere)
  @param - desired CURRENT status
  @return - none
*/
void Cell::SetCurrentCellStatus(bool stat){
    isAlive_ = stat;
}

/**
  Sets the CURRENT Cell status to the requested one (useful for taking turns)
  @param - desired NEXT status
  @return - none
*/
void Cell::SetNextCellStatus(bool nstat){
    nextState_ = nstat; //change the next status
}

/**
  Sets the color based on Cell Status
  @param - desired cell color (in the form of Qcolor)
*/
void Cell::SetColor(QColor color){
    QColor white(255,255,255); //just plain white
     this->previous_color_ = color; //set the previous color, so that the cell won't flip to defaultPink when clicked

    if(isAlive_){
        this->color_ = color; //set the newest alive color
    }
    else{
        this->color_ = white; //reset to white if dead
    }
    //now actually update the color!
    update();
}

/**
  Makes it so the == operator will have the behavior that you
  expect when comparing Cells.
  (saved this from old homework. Thought it would be useful early on, but I don't need it...)
  @param first Cell left hand side of the expression
  @param other Cell right hand side of the expression
*/
bool operator==(const Cell &first, const Cell &other) {
  return first.x_ == other.x_ && first.y_ == other.y_;
}


/**
 * Called whenever a cell is clicked
 * Originally used for debugging, now it changes the status and flips the color!
 * @param - none
 * @return - none
 */
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "x: " << x_ /25;
    qDebug() << "y: " << y_ /25;

    isAlive_ = !isAlive_; //toggle alive status
    SetColor(previous_color_);

    //update this QGraphicsItem (force it to re-draw)
}

/**
 * Changes the Cell's CURRENT status to the NEXT one, effectively "taking a turn" for this cell
 * @param - none
 * @return - none
 */
void Cell::step_cell(){
    isAlive_ = nextState_; //update this cell with it's next state!
}

