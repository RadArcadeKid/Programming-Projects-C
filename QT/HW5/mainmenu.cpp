#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "tutorial.h"
#include "mainwindow.h"
//JAKE HENSON - HW5

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_howToPlayButton_clicked()
{
    Tutorial tutorial_window;
    tutorial_window.setModal(true);
    tutorial_window.exec();
}

void MainMenu::on_pvpButton_clicked()
{
    main_game.SetGameType(0);
    main_game.show();
    this->close();
}
