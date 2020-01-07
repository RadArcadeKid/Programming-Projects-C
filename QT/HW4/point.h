#ifndef POINT_H
#define POINT_H

#include <QColor>
#include <QGraphicsItem>

class Point : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Point(QColor color, const int x, const int y);  // constructor

    int get_x() const { return x_; }  // inline member function
    int get_y() const { return y_; }  // inline member function

    double Distance(const Point &other) const;  // member function

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() { return width_; }

// in point.h
signals:
    void PointSelected(Point * p);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;



private:
  int x_;
  int y_;
  QColor color_;

  static const int width_ = 20;

  // if you declare the operator as a friend, then it isn't
  // part of the object
  // friend will let this method access the private fields
  friend bool operator==(const Point &first, const Point &other);
};  // class Point



#endif // POINT_H
