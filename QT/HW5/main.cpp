#include "mainwindow.h"
#include "mainmenu.h"
#include <QApplication>
//JAKE HENSON - HW5

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

    MainMenu m;
    m.show();
    return a.exec();
}
