#ifndef CELL_H
#define CELL_H

#include <QColor>
#include <QGraphicsItem>
//JAKE HENSON - HW4
//cell.h
//Header file for cell object

class Cell : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Cell(const int x, const int y);  // constructor

    int get_x() const { return x_ /25; }  //return x_/25 (to account for cell width)
    int get_y() const { return y_ /25; }  //return y_/25 (to account for cell height)
    bool get_Cell_Current_Status() { return isAlive_; }  //returns the current status of the cell
    bool get_Cell_Next_Status() { return nextState_; } //returns the next status of the cell
    QColor get_current_color() {return color_; } //returns the color of the cell

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() { return width_; }

    void RandomInitialStatus(); //randomly called once the cell is initialized

    void SetCurrentCellStatus(bool stat); //sets the status based on input

    void SetNextCellStatus(bool nstat); //set the NEXT status of the cell based on input

    void SetColor(QColor alive_color); //sets color of cell

    void step_cell(); //changes the next status to current status

signals:
    void CellSelected(Cell * c);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  int x_; //x position on the grid
  int y_; //y position on the grid
  QColor color_; //cell's current color
  QColor previous_color_; //cell's previous color (used for flipping the cell)
  bool isAlive_; //used for determining the current status of the cell (true = alive, false = dead)
  bool nextState_; //used for determining what the cell will be upon the *next* turn (useful to determining the set)
                   //why do this here? this will be a lot easier than attempting to store all the next statuses within vectors and deal with storing separate turns

  static const int width_ = 25; //width + height of cell. Can be declared const cause it won't change

  friend bool operator==(const Cell &first, const Cell &other);
};  // class Cell


#endif // CELL_H
