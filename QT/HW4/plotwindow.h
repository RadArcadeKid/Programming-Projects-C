#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <string>
#include <QTimer>
#include "cell.h"
#include "graph.h"
#include "bar.h"
//JAKE HENSON - HW4
//PlotWindow.h
//Header file for main object, UI control, and graph + grid

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = 0);
    ~PlotWindow();


    void InitializeGrid();

    void DisplayGrid();

    void CheckCell(Cell * cell);

    void CheckNeighbors(Cell * original, Cell * upleft, Cell * up, Cell * upright, Cell * right, Cell * downright, Cell * down, Cell * downleft, Cell * left);

    void StepAllForward();

    void DisplayLabels();

    int GetNumCellsAlive();

    int GetPopulationPercentage();

    void InitializeGraph();

    void AddBar();

    void RedrawBars();


private slots:

    void CellClickedSlot(Cell * cell);

    void on_stepButton_clicked();

    void on_playButton_clicked();

    void timer_slot();

    void on_pauseButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::PlotWindow *ui;

    QGraphicsScene *scene;

    QTimer *timer;

   // std::vector<int> rows_; //originally had this as ints, until I realized it was easier to just
   // std::vector<int> cols_; //use the actual cell objects. I don't use these anywhere...


    std::vector<Cell *> row_vec_; //a vector for storing all rows of cells
    std::vector<Cell *> col_vec_; //a vector for storing all columns of cells


    //2d vector to store both rows and columns!
    std::vector<std::vector<Cell *>> grid_vec_; //a vector to store the grid into

    //A vector of all the different Qcolors to switch to between turns!
    QColor colors_vec_[10] = {QColor(255,0,255), QColor(255,0,111),
                          QColor(255,0,10), QColor(255, 34, 0),
                          QColor(255, 102, 0), QColor(255, 183, 0),
                          QColor(72, 255, 0), QColor(0, 255, 238),
                          QColor(0, 102, 255), QColor(106, 0, 255)};

    int color_index_; //used to store the index of the color per turn

    std::vector<Bar *> bars_vec_; //a vector to store all of the bars for the graph!
    //Why isn't this in, say, graph.cpp, you might ask?
    //Well - I had TONS of issues actually adding the bars to the scene
    //from that object instead of just doing it in this one with the UI
    //I tried including this file (plotwindow) into graph.h but then the whole updating thing made this really confusing
    //and QT wasn't having it...
    //For the sake of time, this bars_vec_ lives in this object so it can interact with the UI easily
    //I could probably implement it better in the future, but I don't have tons of time right now...

    int turn_; //keeps track of the current turn

    int bar_placement_val_; //keeps track of where to place the bar in relation to the rest of the graph

    float slider_tracker_;  //determines how far the slider is moved, used for speed label + time

};

#endif // PLOTWINDOW_H
