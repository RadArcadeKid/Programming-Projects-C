/**
	JACOB (JAKE) HENSON - 105963531 - jahe4178@colorado.edu 
	Homework 1
	Main.cpp - runs the actual game using the various other files like the player and the maze
	RUNNING RELIES ON ALL PREVIOUS FILES (Player.h, Player.cpp, Maze.cpp. Maze.h) to be preset 
	
	**HOW TO RUN** - 
	1. Use the Makefile and type "make" to compile, if it hasn't already (type "make clean" to recompile if you have)
	2. Type "./maze" to start the file and play the game!
*/
#include <iostream>  //include iostream to std out and std in 
#include "Player.h" //include player so the player can be player 
#include "Maze.h"  //include the maze .cpp so that the maze can be accessed and the game will have a board and rules

int main(){
	
	//initialize a maze. The rest is taken care of in NewGame() and the Maze/Board constructor 
	//because Maze's constructor ties directly to NewGame(), there is literally no need to do much else in main! 
	Maze m1; 
}