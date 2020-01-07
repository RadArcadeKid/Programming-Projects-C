/**
DO NOT REPRODUCE WITHOUT CREDIT TO THE ORIGINAL AUTHOR

	JACOB (JAKE) HENSON
	Homework 1
	Player.cpp - creates and takes in various operations on the player for the game and is the primary focal point for the game
	relies on Player.h to function
	Called internally as a player and externally by the Maze/Board functions in order to run the program
*/
#include <vector>   //include vector for use of vector objects later
#include <iostream> //include iostream for print statements
#include "Player.h" //include the header file with class definitions


/**
	Constructor for Player
	builds the player object, sets name and is_human status with passed-in values
*/
Player::Player(const std::string name, const bool is_human)
	: name_(name), is_human_(is_human) {

	if(is_human){ //change player's position to 0,0 but only if they're the human player
		pos_.row = 0;
		pos_.col = 0;
	}
	else{
		pos_.row = 2;
		pos_.col = 1;
	}
	ChangePoints(0);
}


/**
	ChangePoints changes the number of points the player has based on the input
*/
void Player::ChangePoints(const int x){
	points_ += x;
}


/**
	SetPosition sets a new position for the player based on the input passed-in
*/
void Player::SetPosition(Position pos){
	pos_ = pos;
}


/**
     ToRelativePosition is a function used to translate positions into directions relative to the player (up, down, etc)
*/
std::string Player::ToRelativePosition(Position other){

	if(pos_.row == other.row+1 && pos_.col == other.col){ //the position of other is exactly 1 row above on the same column (up)
		return "UP";
	}
	else if(pos_.row == other.row && pos_.col == other.col+1){ //the position of other is 1 column to the left on the same row (left)
		return "LEFT";
	}
	else if(pos_.row == other.row && pos_.col == other.col-1){ //the position of other is 1 column to the right on the same row (right)
		return "RIGHT";
	}
	else if(pos_.row == other.row-1 && pos_.col == other.col){ //the position of other is exactly 1 row below on the same column (down)
		return "DOWN";
	}

	return ""; //else, return nothing
}


/**
	//Convert this player to a string representation of their name and points

*/
std::string Player::Stringify(){
	return name_ + " has " + std::to_string(points_) + " points,";
}
