#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QDialog>
//JAKE HENSON - HW5
//Tutorial.h - used for displaying a dialogue box of the tutorial window
namespace Ui {
class Tutorial;
}

class Tutorial : public QDialog
{
    Q_OBJECT

public:
    explicit Tutorial(QWidget *parent = nullptr);
    ~Tutorial();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Tutorial *ui;
};

#endif // TUTORIAL_H
