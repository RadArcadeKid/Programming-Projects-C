#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <vector>
#include <string>
#include <QDebug>
#include <QTimer>

#include "boardcell.h"
#include "piece.h"
//JAKE HENSON - HW5
//GameLoop.h - used for the logic of the base game - Run and called in MainWindow

class GameLoop {

public:
    GameLoop();

    void InitializeBoard();

    int get_current_column() { return current_col_; }

    void SetCurrentColumn(int s) {current_col_ = s; } //manually set this for automation later

    std::vector<std::vector<BoardCell *>> get_board_vec() { return grid_vec_; }

    int get_player() { return player_; }

    Piece * AddPiece(std::string piecetype);

    ConvertPowerup * AddPowerup(std::string piecetype);

    int ToggleTurn();

    bool CanMoveHere();

    int GetCurrentRow();

    void MoveLeft();
    void MoveRight();

    bool IsBoardFull();


    void MovePiecesDown();
    void DropRow();

    int CheckIfWinner();

    int GetPowerUpQty(std::string powerupName); //returns the qty of the requested powerup
    int decrementPowerUpQty(std::string powerupName); //decrements the requested power up qty by 1 for the current player

    int ConvertWinner(std::string currentPieceColor);

    void ResetGame();

    void increment_num_games_won(int winner);

    int get_num_games_won(int player);

private:
    std::vector<std::vector<BoardCell *>> grid_vec_; //a vector to store the grid into
    std::vector<BoardCell *> col_vec_; //a vector for storing all columns of cells

    int available_moves[7]; //a vector to store each column's valid move

    int current_col_;

    int player_;

    int neutral_pieces_qty_p1_;
    int neutral_pieces_qty_p2_;
    int converter_pieces_qty_p1_;
    int converter_pieces_qty_p2_;

    int num_games_won_p1_;
    int num_games_won_p2_;

};

#endif // GAMELOOP_H
