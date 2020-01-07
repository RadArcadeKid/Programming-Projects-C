#ifndef WINNERDIALOG_H
#define WINNERDIALOG_H

#include <QDialog>
//JAKE HENSON - HW5
//WinnerDialogue.h - used for displaying a dialogue box of the winner window
namespace Ui {
class WinnerDialog;
}

class WinnerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinnerDialog(QWidget *parent = nullptr);
    ~WinnerDialog();

    void SetWinner(int winner, int win_qty_p1, int win_qty_p2);

signals:
    void ReadyToResetSig();

private slots:
    void on_quitButton_clicked();

    void on_playAgainButton_clicked();

private:
    Ui::WinnerDialog *ui;

};

#endif // WINNERDIALOG_H
