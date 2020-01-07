#ifndef PIECEICON_H
#define PIECEICON_H
#include <QColor>
#include <QGraphicsItem>
#include <string>
//JAKE HENSON - HW5
//PieceIcon.h - used for the icon of the piece for the powerup

class PieceIcon : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    PieceIcon(const int x, const int y, std::string name);  // constructor

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

signals:
    void PieceSelected(PieceIcon * p);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  int x_; //x position on the grid
  int y_; //y position on the grid
  QColor color_;
  std::string name_; //name for da icon


  static const int width_height_ = 50; //width + height of CheckerPiece. Can be declared const cause it won't change
};

#endif // PIECEICON_H
