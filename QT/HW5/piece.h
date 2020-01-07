#ifndef PIECE_H
#define PIECE_H
#include <QColor>
#include <QGraphicsItem>
#include <string>
//JAKE HENSON - HW5
//Piece.h - used to draw and access each different piece.
//logic is checked and modified in GameLoop, but shown and drawn/updated in MainWindow

//NOTE - there is also an inhereted object here called ConvertPowerup
//this object is used for the Convert powerup in the game, and behaves differently than the normal powerup piece

class Piece : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Piece(const int x, const int y, std::string name);  // constructor

    void setPieceIdentity(std::string name);

    int get_x() const { return x_; }
    int get_y() const { return y_; }

    //FOR THE USE OF INHERITENCE
    //std::string getPieceName();

    virtual std::string getPieceName();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_size() { return width_height_; }

private:
  int x_; //x position on the grid
  int y_; //y position on the grid
  QColor color_;

  static const int width_height_ = 84; //width + height of CheckerPiece. Can be declared const cause it won't change
};


//Now for the inherited powerup piece!!
//Fulfills the requirements for the inheritted object
class ConvertPowerup : public Piece {
    Q_OBJECT
   public:
    ConvertPowerup(int x, int y, int player):
        Piece(x,y, "converter"){
        real_x_ = x;
        real_y_ = y;
        player_ = player;
    } // constructor

    std::string getPieceName() override { return "converter"; } //for use of virtual

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

   private:
    int real_x_;
    int real_y_;
    int player_;
    const int width_height_ = 84;
};

#endif // PIECE_H
