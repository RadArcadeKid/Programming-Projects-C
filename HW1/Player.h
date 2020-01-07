/**
DO NOT REPRODUCE WITHOUT CREDIT TO THE ORIGINAL AUTHOR

	JACOB (JAKE) HENSON
	Homework 1
	Player.h - acts as a blueprint for the Player and Position classes, which are used later to tell the function how to run
	demonstrated in the Player.cpp
*/
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string> //include type string so that we can use it throughout

struct Position {
	int row;
	int col;

	// already implemented for you!
	bool operator==(const Position &other) {
		return row == other.row && col == other.col;
	}
};


class Player {
public:
	Player(const std::string name, const bool is_human);  // constructor

	// These are already implemented for you
	std::string get_name() const {return name_; }  // inline member function
	int get_points() const {return points_; }  // inline member function
	Position get_position() const {return pos_; }  // inline member function
	bool is_human() const {return is_human_; }  // inline member function

//	// TODO: implement the following functions
//	// You MUST implement the following functions
	void ChangePoints(const int x);
//
//	// set a new position for this player
	void SetPosition(Position pos);
//
//	// You may want to implement these functions as well
//	// ToRelativePosition is a function we used to translate positions
//	// into directions relative to the player (up, down, etc)
	std::string ToRelativePosition(Position other);
//
//	// Convert this player to a string representation of their name and points
	std::string Stringify();
//
//	// You may add other functions as needed/wanted

private:
	std::string name_;
	int points_ = 0;
	Position pos_;
	bool is_human_;

	// You may add other fields as needed

}; // class Player

#endif  // _PLAYER_H_
