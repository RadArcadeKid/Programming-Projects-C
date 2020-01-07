#ifndef BOARDCELL_H
#define BOARDCELL_H
#include <QColor>
#include <QGraphicsItem>
#include "piece.h"
//JAKE HENSON - HW5
//Boardcell.h - used for the board to draw it and store the piece inside. Run in GameLoop and used in MainWindow
class BoardCell : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    BoardCell(const int x, const int y);  // constructor

    int get_x() const { return x_/90; }
    int get_y() const { return y_/90; }

    void setPiece(std::string piecename);

    void setPiece(std::string piecename, int player); //overloaded one for setting the Powerup

    Piece * getPiece() { return thisPiece_; } //returns a pointer to this piece!

    ConvertPowerup * getPowerup() { return thisPowerup_; }

    //ConvertPowerup * getPowerup() { return thisPowerup_; } //returns a pointer to this piece!


    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_size() { return width_height_; }

    void RepaintThisCell();

private:
  int x_; //x position on the grid
  int y_; //y position on the grid
  QColor color_; //the color of the square, currently set as default white
  Piece * thisPiece_; //stores the piece in the spot on the baord
  ConvertPowerup * thisPowerup_;

  static const int width_height_ = 90; //width + height of BoardCell. Can be declared const cause it won't change

};

#endif // BOARDBoardCell_H
