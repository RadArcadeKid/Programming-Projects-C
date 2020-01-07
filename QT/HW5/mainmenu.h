#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include "tutorial.h"
#include "mainwindow.h"
//JAKE HENSON - HW5
//MainMenu.h - used for the main menu of the game - Run from main
namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_howToPlayButton_clicked();

    void on_pvpButton_clicked();

private:
    Ui::MainMenu *ui;

    MainWindow main_game;

};

#endif // MAINMENU_H
