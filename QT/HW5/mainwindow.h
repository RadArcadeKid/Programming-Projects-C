#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <string>
#include <QDebug>
#include <QTimer>

#include "boardcell.h"
#include "piece.h"
#include "gameloop.h"
#include "selector.h"
#include "bar.h"
//JAKE HENSON - HW5
//MainWindow.h - used to allow the user to play the game, and used for the base functionality for the whole game
//Works closely with GameLoop and the signals and slots to get user input

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetGameType(int gm);

    void DrawBoard();

    void RowDropScene();

    void DrawPowerups();

    void UpdateLabels();

    void UpdateGraph();

    void StartGame();

    void SpawnWinnerPopup(int winner);

private slots:
    void on_drop_button_clicked();

    void on_left_button_clicked();

    void on_right_button_clicked();

    void NeutralPiece_clicked();

    void ConverterPiece_clicked();


    void ReadyToReset();


private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    QGraphicsScene *icon_scene;

    QGraphicsScene *graph_scene;

    QTimer *timer;

    GameLoop game_; //the game will be played here!

    Selector * select_obj_;

    Bar * p1_bar; //used for storing the bar graphs
    Bar * p2_bar; //used for storing the bar graphs

    int gamemode_;
};

#endif // MAINWINDOW_H
