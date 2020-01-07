#ifndef GRAPH_H
#define GRAPH_H

#include <QColor>
#include <QGraphicsItem>
#include "bar.h"
//JAKE HENSON - HW4
//PlotWindow.h
//Header file for graph object

class Graph : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Graph();  // constructor

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

signals:

protected:

private:
  QColor color_;

  static const int width_ = 525; //can be declared once here. These values won't change
  static const int height_ = 100;

};


#endif // GRAPH_H
