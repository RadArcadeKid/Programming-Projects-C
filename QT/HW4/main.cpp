#include "plotwindow.h" //only need this, everything else is included back in plotwindow
#include <QApplication>
//JAKE HENSON - HW4
//main.cpp
//Initializes the main running of the QApplication and starts the program

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlotWindow w;
    w.show();

    return a.exec();
}
