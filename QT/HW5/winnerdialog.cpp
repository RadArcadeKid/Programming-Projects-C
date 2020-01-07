#include "winnerdialog.h"
#include "ui_winnerdialog.h"
//JAKE HENSON - HW5

WinnerDialog::WinnerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinnerDialog)
{
    ui->setupUi(this);
}

WinnerDialog::~WinnerDialog()
{
    delete ui;
}

void WinnerDialog::SetWinner(int winner, int win_qty_p1, int win_qty_p2){

    //update who won the game
    std::string winner_string = "Player " + std::to_string(winner) + " has won the game!!";
    QString q_win_string(winner_string.c_str());
    ui->winner_dialog->setText(q_win_string);

    //update winner labels:
    std::string p1_win_label = "Player 1 has " + std::to_string(win_qty_p1) + " win(s)";
    QString p1_final_label(p1_win_label.c_str());
    ui->p1_wins_label->setText(p1_final_label);

    std::string p2_win_label = "Player 2 has " + std::to_string(win_qty_p2) + " win(s)";
    QString p2_final_label(p2_win_label.c_str());
    ui->p2_wins_label->setText(p2_final_label);

}

void WinnerDialog::on_quitButton_clicked()
{
    exit(0); //quit the game once quit is clicked
}

void WinnerDialog::on_playAgainButton_clicked()
{
    //call main_window's game and reset_game!
    emit ReadyToResetSig();
    close();
}
