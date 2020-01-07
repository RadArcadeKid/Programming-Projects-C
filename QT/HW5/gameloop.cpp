#include "gameloop.h"
//JAKE HENSON - HW5

GameLoop::GameLoop()
{
    current_col_ = 3; //by default, the current column should start in middle of the scene


    num_games_won_p1_ = 0;
    num_games_won_p2_ = 0;

    neutral_pieces_qty_p1_ = 2;
    neutral_pieces_qty_p2_ = 2;

    converter_pieces_qty_p1_ = 1;
    converter_pieces_qty_p2_ = 1;


    InitializeBoard();

}


void GameLoop::InitializeBoard(){

    //populate the board with all the cells
    for(int col = 0; col < 7; col++){
        for(int row = 0; row < 6; row++){
            BoardCell * grid_cell = new BoardCell((col), (row));
            col_vec_.push_back(grid_cell);
            //scene->addItem(grid_cell);
        }
        grid_vec_.push_back(col_vec_); //populate grid vec with vector of columns!
        col_vec_ = {}; //reset col_vec back to 0, to be populated again!
    }

    //set the available moves for all columns to all row 5 (i.e., the bottom row of the board is the places where the players can go)
    for(int i = 0; i < 7; i++){
        available_moves[i] = 5;
    }

    player_ = 1;
}


/**
 * @brief GameLoop::MoveLeft - moves the current_column to the left (decrements it)
 * @param none
 * @return none
 */
void GameLoop::MoveLeft(){
    if(current_col_ > 0){
        current_col_-= 1;
    }
}


/**
 * @brief GameLoop::MoveLeft - moves the current_column to the right (increments it)
 * @param none
 * @return none
 */
void GameLoop::MoveRight(){
    if(current_col_ < 6){
        current_col_+= 1;
    }
}


/**
 * @brief GameLoop::MoveLeft - determines whether the player is allowed to move here based on the number of avaliable moves
 * @param none
 * @return none
 */
bool GameLoop::CanMoveHere(){
    if(available_moves[current_col_] == -1){
        return false;
    }
    else{
        return true;
    }
}


/**
 * @brief GameLoop::MoveLeft - Returns the avaliable row - useful for the converter piece because my implementation of it
 *           is kinda janky
 * @param none
 * @return none
 */
int GameLoop::GetCurrentRow(){
    return available_moves[current_col_];
}

/**
 * @brief GameLoop::AddPiece - adds a piece to the scene where the user would like. Also updates the avaliable rows
 * @param col - the desired column where the piece will go
 * @return returns this newly piece object so MainWindow can draw it!
 *         Should the player try to drop a piece where the column is full, this will return nullptr
 *         and not allow them to drop the piece
 */
Piece * GameLoop::AddPiece(std::string piecetype){
    int row = available_moves[current_col_]; //get the avaliable row from the avaliable_moves at the current column
    if(row != -1){ //if we're dealing with a valid row
        grid_vec_[current_col_][row]->setPiece(piecetype);

        available_moves[current_col_] -= 1;
        return grid_vec_[current_col_][row]->getPiece();
    }
    else{
        return nullptr;
    }
}

/**
 * @brief GameLoop::AddPowerup - Adds the powerup for the converter (needs to be a new function
 * because it's functionality is different and there's a whole new object type associated with it)
 * @param piecetype - the converter piece (or maybe more if I decide to add more powerups)
 * @return
 */
ConvertPowerup * GameLoop::AddPowerup(std::string piecetype){
    int row = available_moves[current_col_]; //get the avaliable row from the avaliable_moves at the current column
    if(row != -1){ //if we're dealing with a valid row
            grid_vec_[current_col_][row]->setPiece(piecetype, player_);
            if(row < 5){ //if we're not on the bottom row
                grid_vec_[current_col_][row+1]->setPiece("empty"); //rest to empty first...
                if(player_ == 1){
                    grid_vec_[current_col_][row+1]->setPiece("blue"); //set the piece below it to the player's piece
                }
                if(player_ == 2){
                    grid_vec_[current_col_][row+1]->setPiece("pink"); //set the piece below it to the player's piece
                }
            }

        available_moves[current_col_] -= 1; //remove this space from the scene
        return grid_vec_[current_col_][row]->getPowerup(); //return the powerup!
    }
    else{
        return nullptr; // if we hanve't placed anything, don't return anything
    }
}

/**
 * @brief GameLoop::ToggleTurn - Toggles which player is currently going
 * @return
 */
int GameLoop::ToggleTurn(){
    int current_player = player_;

    //flip da player
    if(current_player == 1) player_ = 2;
    else if(current_player == 2) player_ = 1;


    return player_;

}


/**
 * @brief GameLoop::IsBoardFull - Checks to see whether all of the spaces in the board have been filled by other pieces
 * @return returns true if the board is full, false otherwise
 */
bool GameLoop::IsBoardFull(){
    int num_cols_filled = 0;

    for(int i = 0; i < 7; i++){
        if(available_moves[i] == -1) num_cols_filled++; //increment the number of columns filled if it's full
    }


    if(num_cols_filled == 7) return true; //we've filled all columns then the board is full
    else return false;
}

/**
 * @brief GameLoop::MovePiecesDown - moves all of the pieces down on the board. Useful for RowDrop
 */
void GameLoop::MovePiecesDown(){
    //move all of the pieces in each column down by one
    for(int col = 0; col < 7; col++){
        for(int row = 5; row > 0; row--){
            grid_vec_[col][row]->setPiece( grid_vec_[col][row-1]->getPiece()->getPieceName() );
        }
    }
}

/**
 * @brief GameLoop::DropRow - drops the bottom row of pieces and resets available moves
 */
void GameLoop::DropRow(){

    //drop the top row
    for(int i = 0; i < 7; i++){
        grid_vec_[i][0]->setPiece("empty"); //empty this piece
        available_moves[i]++; //increment the number of avaliable moves at this column
    }
}


/**
 * @brief GameLoop::CheckIfWinner - checks all spaces in the board to see if there is a winnder!
 * @return
 *      - returns 1 if player 1 is the winner
 *      - returns 2 if player 2 is the winner
 *      - returns 0 is nobody is the winner yet!
 */
int GameLoop::CheckIfWinner(){
    int winner = 0; //reset the winner to 0 each time it checks a piece

    for(int col = 0; col < 7; col++){
        for(int row = 0; row < 6; row++){
            //if there actually is a space on this piece
            if(grid_vec_[col][row]->getPiece() != nullptr){

             //and if that piece is either blue or pink...
             if(grid_vec_[col][row]->getPiece()->getPieceName() == "blue" || grid_vec_[col][row]->getPiece()->getPieceName() == "pink"){
            //----------------------------------
                std::string current_piece_color = grid_vec_[col][row]->getPiece()->getPieceName(); //find out the current piececolor

                //CHECK ALL SPOTS NEAR THE PIECE TO DETERMINE IF THERE'S A CONNECT FOUR
                if(col < 3){
                    //check right
                    if(grid_vec_[col+1][row]->getPiece() != nullptr && grid_vec_[col+1][row]->getPiece()->getPieceName() == current_piece_color){
                        if(grid_vec_[col+2][row]->getPiece() != nullptr && grid_vec_[col+2][row]->getPiece()->getPieceName() == current_piece_color){
                            if(grid_vec_[col+3][row]->getPiece() != nullptr && grid_vec_[col+3][row]->getPiece()->getPieceName() == current_piece_color){
                                winner = ConvertWinner(current_piece_color);

                                //repaint cells
                                grid_vec_[col][row]->RepaintThisCell();
                                grid_vec_[col+1][row]->RepaintThisCell();
                                grid_vec_[col+2][row]->RepaintThisCell();
                                grid_vec_[col+3][row]->RepaintThisCell();
                            }
                        }
                    }

                    if(row <= 2){
                        //check down
                        if(grid_vec_[col][row+1]->getPiece() != nullptr && grid_vec_[col][row+1]->getPiece()->getPieceName() == current_piece_color){
                            if(grid_vec_[col][row+2]->getPiece() != nullptr && grid_vec_[col][row+2]->getPiece()->getPieceName() == current_piece_color){
                                if(grid_vec_[col][row+3]->getPiece() != nullptr && grid_vec_[col][row+3]->getPiece()->getPieceName() == current_piece_color){
                                    winner = ConvertWinner(current_piece_color);

                                    //repaint cells
                                    grid_vec_[col][row]->RepaintThisCell();
                                    grid_vec_[col][row+1]->RepaintThisCell();
                                    grid_vec_[col][row+2]->RepaintThisCell();
                                    grid_vec_[col][row+3]->RepaintThisCell();
                                }
                            }
                        }

                        //check downright
                        if(grid_vec_[col+1][row+1]->getPiece() != nullptr && grid_vec_[col+1][row+1]->getPiece()->getPieceName() == current_piece_color){
                            if(grid_vec_[col+2][row+2]->getPiece() != nullptr && grid_vec_[col+2][row+2]->getPiece()->getPieceName() == current_piece_color){
                                if(grid_vec_[col+3][row+3]->getPiece() != nullptr && grid_vec_[col+3][row+3]->getPiece()->getPieceName() == current_piece_color){
                                    winner = ConvertWinner(current_piece_color);

                                    //repaint cells
                                    grid_vec_[col][row]->RepaintThisCell();
                                    grid_vec_[col+1][row+1]->RepaintThisCell();
                                    grid_vec_[col+2][row+2]->RepaintThisCell();
                                    grid_vec_[col+3][row+3]->RepaintThisCell();
                                }
                            }
                        }


                    }
                }

                else if(col == 3){
                    //check right
                    if(grid_vec_[col+1][row]->getPiece() != nullptr && grid_vec_[col+1][row]->getPiece()->getPieceName() == current_piece_color){
                        if(grid_vec_[col+2][row]->getPiece() != nullptr && grid_vec_[col+2][row]->getPiece()->getPieceName() == current_piece_color){
                            if(grid_vec_[col+3][row]->getPiece() != nullptr && grid_vec_[col+3][row]->getPiece()->getPieceName() == current_piece_color){
                                winner = ConvertWinner(current_piece_color);

                                grid_vec_[col][row]->RepaintThisCell();
                                grid_vec_[col+1][row]->RepaintThisCell();
                                grid_vec_[col+2][row]->RepaintThisCell();
                                grid_vec_[col+3][row]->RepaintThisCell();
                            }
                        }
                    }

                    if(row <= 2){
                        //check down
                        if(grid_vec_[col][row+1]->getPiece() != nullptr && grid_vec_[col][row+1]->getPiece()->getPieceName() == current_piece_color){
                            if(grid_vec_[col][row+2]->getPiece() != nullptr && grid_vec_[col][row+2]->getPiece()->getPieceName() == current_piece_color){
                                if(grid_vec_[col][row+3]->getPiece() != nullptr && grid_vec_[col][row+3]->getPiece()->getPieceName() == current_piece_color){
                                    winner = ConvertWinner(current_piece_color);

                                    //repaint cells
                                    grid_vec_[col][row]->RepaintThisCell();
                                    grid_vec_[col][row+1]->RepaintThisCell();
                                    grid_vec_[col][row+2]->RepaintThisCell();
                                    grid_vec_[col][row+3]->RepaintThisCell();
                                }
                            }
                        }

                        //check downright
                        if(grid_vec_[col+1][row+1]->getPiece() != nullptr && grid_vec_[col+1][row+1]->getPiece()->getPieceName() == current_piece_color){
                            if(grid_vec_[col+2][row+2]->getPiece() != nullptr && grid_vec_[col+2][row+2]->getPiece()->getPieceName() == current_piece_color){
                                if(grid_vec_[col+3][row+3]->getPiece() != nullptr && grid_vec_[col+3][row+3]->getPiece()->getPieceName() == current_piece_color){
                                    winner = ConvertWinner(current_piece_color);

                                    //repaint cells
                                    grid_vec_[col][row]->RepaintThisCell();
                                    grid_vec_[col+1][row+1]->RepaintThisCell();
                                    grid_vec_[col+2][row+2]->RepaintThisCell();
                                    grid_vec_[col+3][row+3]->RepaintThisCell();
                                }
                            }
                        }

                        //check downleft
                        if(grid_vec_[col-1][row+1]->getPiece() != nullptr && grid_vec_[col-1][row+1]->getPiece()->getPieceName() == current_piece_color){
                            if(grid_vec_[col-2][row+2]->getPiece() != nullptr && grid_vec_[col-2][row+2]->getPiece()->getPieceName() == current_piece_color){
                                if(grid_vec_[col-3][row+3]->getPiece() != nullptr && grid_vec_[col-3][row+3]->getPiece()->getPieceName() == current_piece_color){
                                    winner = ConvertWinner(current_piece_color);

                                    //repaint cells
                                    grid_vec_[col][row]->RepaintThisCell();
                                    grid_vec_[col-1][row+1]->RepaintThisCell();
                                    grid_vec_[col-2][row+2]->RepaintThisCell();
                                    grid_vec_[col-3][row+3]->RepaintThisCell();
                                }
                            }
                        }

                    }
                }
                else if(col >3){
                    if(row <= 2){
                        //check down
                        if(grid_vec_[col][row+1]->getPiece() != nullptr && grid_vec_[col][row+1]->getPiece()->getPieceName() == current_piece_color){
                            if(grid_vec_[col][row+2]->getPiece() != nullptr && grid_vec_[col][row+2]->getPiece()->getPieceName() == current_piece_color){
                                if(grid_vec_[col][row+3]->getPiece() != nullptr && grid_vec_[col][row+3]->getPiece()->getPieceName() == current_piece_color){
                                    winner = ConvertWinner(current_piece_color);

                                    //repaint cells
                                    grid_vec_[col][row]->RepaintThisCell();
                                    grid_vec_[col][row+1]->RepaintThisCell();
                                    grid_vec_[col][row+2]->RepaintThisCell();
                                    grid_vec_[col][row+3]->RepaintThisCell();
                                }
                            }
                        }

                        //check downleft
                        if(grid_vec_[col-1][row+1]->getPiece() != nullptr && grid_vec_[col-1][row+1]->getPiece()->getPieceName() == current_piece_color){
                            if(grid_vec_[col-2][row+2]->getPiece() != nullptr && grid_vec_[col-2][row+2]->getPiece()->getPieceName() == current_piece_color){
                                if(grid_vec_[col-3][row+3]->getPiece() != nullptr && grid_vec_[col-3][row+3]->getPiece()->getPieceName() == current_piece_color){
                                    winner = ConvertWinner(current_piece_color);

                                    //repaint cells
                                    grid_vec_[col][row]->RepaintThisCell();
                                    grid_vec_[col-1][row+1]->RepaintThisCell();
                                    grid_vec_[col-2][row+2]->RepaintThisCell();
                                    grid_vec_[col-3][row+3]->RepaintThisCell();
                                }
                            }
                        }

                    }
                }

            //-----------------------------------
            }

            }//end checking piecetype
        }
    }
    increment_num_games_won(winner); //should increment the number of games won once the game is actually a winner (won't do anything if it's 0)
    return winner;
}


/**
 * @brief GameLoop::ConvertWinner - coonvers the winner to an int value
 * a last minute function because i got a little lost in the logic of theCheckIfWinner()
 * @param current_piece_color
 * @return returns the temporary winner, used for actually determing the winner in CheckIfWinner()
 */
int GameLoop::ConvertWinner(std::string current_piece_color){
    int temp_winner;
    if(current_piece_color == "blue") temp_winner = 1;
    if(current_piece_color == "pink") temp_winner = 2;

    return temp_winner;
}

/**
 * @brief GameLoop::GetPowerUpQty - Gets powerup quantity for current player
 * @param powerupName - which powerup to get the quantity of
 * @return returns the powerup quantity for the current player
 */
int GameLoop::GetPowerUpQty(std::string powerupName){
    if(powerupName == "neutral"){
        if(player_ == 1) return neutral_pieces_qty_p1_;
        else if(player_ == 2) return neutral_pieces_qty_p2_;
    }
    else if(powerupName == "converter"){
        if(player_ == 1) return converter_pieces_qty_p1_;
        else if(player_ == 2) return converter_pieces_qty_p2_;
    }
}

/**
 * @brief GameLoop::decrementPowerUpQty - Removes 1 to the powerup quantity
 * @param powerupName - which powerup to decrement
 * @return
 */
int GameLoop::decrementPowerUpQty(std::string powerupName){
    if(powerupName == "neutral"){
        if(player_ == 1) neutral_pieces_qty_p1_--;
        else if(player_ == 2) neutral_pieces_qty_p2_--;
    }
    else if(powerupName == "converter"){
        if(player_ == 1) converter_pieces_qty_p1_--;
        else if(player_ == 2) converter_pieces_qty_p2_--;
    }
}

/**
 * @brief GameLoop::ResetGame - Resets the game!!!
 */
void GameLoop::ResetGame(){
    //set all pieces to empty
    for(int col = 0; col < 7; col++){
        for(int row = 0; row < 6; row++){
            grid_vec_[col][row]->setPiece("empty"); //empty each piece            
        }
        available_moves[col] = 5; //reset all avaliable moves
    }

    //Resets pieces
    neutral_pieces_qty_p1_ = 2;
    neutral_pieces_qty_p2_ = 2;

    converter_pieces_qty_p1_ = 1;
    converter_pieces_qty_p2_ = 1;
}


/**
 * @brief GameLoop::increment_num_games_won - increments the number of games won for the winner!
 * @param winner - the winner of the game, in int form
 */
void GameLoop::increment_num_games_won(int winner){
    if(winner == 1) num_games_won_p1_++; //player 1 won!
    if(winner == 2) num_games_won_p2_++; //player 2 won!
}

/**
 * @brief GameLoop::get_num_games_won - Retrieves the number of games won for the specified player
 * @param player returns the number of games won
 * @return
 */
int GameLoop::get_num_games_won(int player){
    if(player == 1) return num_games_won_p1_;
    else if(player == 2) return num_games_won_p2_;
}
