#ifndef BAR_H
#define BAR_H

#include <QColor>
#include <QGraphicsItem>
//JAKE HENSON - HW5
//Bar.h - used for the bar graph. Run in MainWindow
class Bar : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Bar(const int x, int player);
    int get_x() {return x_; }
    int get_height() { return height_; }

    void setHeight(int numWins);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

signals:

protected:

private:
   int x_; //bar's x position on the graph
   int y_; //bar's y position on the graph
   QColor color_; //bar's current color

  static const int width_ = 50; //bar's width value
  int height_; //bar's height value (is subject to change, so it's not const)

};


#endif // BAR_H
