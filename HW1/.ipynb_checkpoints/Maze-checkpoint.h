/**
	JACOB (JAKE) HENSON - 105963531 - jahe4178@colorado.edu 
	Homework 1
	Maze.h - acts as a blueprint for the Maze and Board classes, which are used later to tell the function how to run  
	demonstrated in the Maze.cpp 
*/
#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector> //include vector so we can use it later
#include <string> //include string just in case we need to use strings
#include "Player.h" //include player.h to access the player clases data and functions from Player 

// you may change this enum as you need
enum class SquareType {Wall, Exit, Empty, Human, Enemy, Treasure}; 

// TODO: implements
std::string SquareTypeStringify(SquareType sq);



class Board {
public:
	Board();
	
	// already implemented in line
	int get_rows() const {return 4; }  // you should be able to change the size of your 
	int get_cols() const {return 4; }  // board by changing these numbers and the numbers in the arr_ field

//	// TODO: you MUST implement the following functions
	SquareType get_square_value(Position pos) const;
//
//	// set the value of a square to the given SquareType
	void SetSquareValue(Position pos, SquareType value);
//
	// get the possible Positions that a Player could move to
	// (not off the board or into a wall)
	std::vector<Position> GetMoves(Player *p);

//	// Move a player to a new position on the board. Return
//	// true if they moved successfully, false otherwise.
	bool MovePlayer(Player *p, Position pos);
//
//	// Get the square type of the exit square
	SquareType GetExitOccupant();
//
//	// You probably want to implement this
//	friend std::ostream& operator<<(std::ostream& os, const Board &b);

private:
	SquareType arr_[4][4];
	
	int rows_; // might be convenient but not necessary
	int cols_;
		
	// you may add more fields, as needed
};  // class Board

class Maze {
public:
	Maze(); // constructor
	
	// initialize a new game, given one human player and 
	// a number of enemies to generate
	void NewGame(Player *human, const int enemies);

	// have the given Player take their turn
	void TakeTurn(Player *p);

	// Get the next player in turn order
	Player * GetNextPlayer();
	
	//A quick an clean function to test the player's input to see if it's in the list of valid positions passed-in
	bool ValidMove(Player *p, std::string move, std::vector<Position> &list_of_positions);
	
	//Controlls the AI enemy's turn 
	void AIEnemyTurn(Player *p, Position current_enemy_pos, std::vector<Position> &list_of_positions);

	// return true if the human made it to the exit 
	// or the enemies ate all the humans
	bool IsGameOver();
	
	// You probably want to implement these functions as well
	// string info about the game's conditions after it is over
	std::string GenerateReport();
	//friend std::ostream& operator<<(std::ostream& os, const Maze &m);

private:
	Board *board_; 
	std::vector<Player *> players_;
	int turn_count_; //NOTE - this is my way of indicating how many turns the player has left, NOT THE index of the player
	
	
	unsigned int current_player_index_; //my own variable to track the current player index

};  // class Maze

#endif  // _MAZE_H_
