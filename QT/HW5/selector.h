#ifndef SELECTOR_H
#define SELECTOR_H
#include <QColor>
#include <QGraphicsItem>
#include "piece.h"
//JAKE HENSON - HW5
//Selector.h - used for the selector to show whose' turn at the top of the game

class Selector : public QObject, public QGraphicsItem {

   Q_OBJECT

public:
   Selector(int x);  // constructor

   //TODO: FIGURE OUT HOW TO ADD A GRAPHICS OBJECT/IMAGE

   void setPieceColor(std::string name);

   std::string getPieceColor() { return name_;}

   void MoveSelector(int col);

   QRectF boundingRect() const override;
   QPainterPath shape() const override;

   void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
 int x_; //x position on the grid
 int y_; //y position on the grid
 QColor color_; //this color
 QColor piece_type_color_; //the color of the piece that Qcolor should be drawing

 std::string name_;

 Piece * thisPiece_; //stores the piece in the spot on the baord

 static const int width_ = 73; //width + height of BoardCell. Can be declared const cause it won't change
 static const int height_ = 90;

};

#endif // SELECTOR_H
