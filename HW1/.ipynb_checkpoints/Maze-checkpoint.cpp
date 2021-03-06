/**
	JACOB (JAKE) HENSON - 105963531 - jahe4178@colorado.edu 
	Homework 1
	Maze.cpp - builds the maze for the game and is run later
	relies on Maze.h and Player.h to run 
	The most important part of this whole assignment 
*/
#include <vector> //include vector for use with vectors 
#include "Maze.h"  //include the Maze.h file to retrieve functions from header 
#include <iostream> //for printing and inputing values 
#include <ctime> //for use with running random and generating random seeds (used with rand() functionality)


/*
	Implementation of SquareType Stringify that will convert the type of SqaureType to a corrosponding string value
	@parameter SquareType sq is a single element we're passing in and returning its value 
*/
std::string SquareTypeStringify(SquareType sq){	
	std::string emojii_string; //to store what the square value is later 
	
	//a switch statement to quickly return each value of the squaretype instead of a bunch of if/else statements
	switch(sq) {
	case SquareType::Wall  : emojii_string = " 🔳 "; break; 
    case SquareType::Empty  : emojii_string =" ⬜ "; break;  
    case SquareType::Exit  : emojii_string =" ✅ "; break; 
    case SquareType::Human  : emojii_string =" 🐈 "; break;  
	case SquareType::Treasure  : emojii_string =" 🐟 "; break; //treasure is a fish! ya know, cause cats love fish! 
    case SquareType::Enemy  : emojii_string =" 🐺 "; break;  			
	}
	
	return emojii_string;  //returns the value of the emojii to build the board with. Much easier to do it this way. 
}


/*
	Constructor for the Board class  
*/
Board::Board(){	
	srand(time(0)); //in order to get truly random numbers, I found that srand must be used when using the rand() function; 
	
	//initalize empty board with player and exit
	for(int x = 0; x < 4; x++){
		for(int y = 0; y < 4; y++){
			
			bool is_wall = (rand() % 100 < 20); //20% chance of walls
 			bool is_treasure = (rand() % 100 < 10); //10% chance of treasure 
			
			if(is_wall == true){
				arr_[x][y] = SquareType::Wall; 
			}
			else if(is_treasure == true){
				arr_[x][y] = SquareType::Treasure; 
			}			
			else{
				arr_[x][y] = SquareType::Empty; 
			}
		}
	}
	arr_[0][0] = SquareType::Human; //initialize player
	arr_[3][3] = SquareType::Exit;   //initialize exit
}

/*
	Implementation for get_square_value, returns the array's value at the specified position's row and column (square value)
	@Position pos is just a position value passed in that the user would like to know 
*/
SquareType Board::get_square_value(Position pos) const{
	return arr_[pos.col][pos.row]; //all we need is to access the array at the specified column and row at the given spot
}; 


/**
	Implementation for SetSquareValue, sets the value of a square to the given SquareType
	@Position pos is a position the user would like to implement, value is what we're setting
*/
void Board::SetSquareValue(Position pos, SquareType value){
	arr_[pos.col][pos.row] = value; 
}

/**
	get the possible Positions that a Player could move to
	(not off the board or into a wall)
*/
std::vector<Position> Board::GetMoves(Player *p){
	Position current_player_pos = p -> get_position(); //declare the player's position so we don't have to keep accessing it in the loops
	
	std::vector<Position> avaliable_positions; //a vector that will be filled with possible positions the player can move  
	
	Position new_pos[4] = { current_player_pos, current_player_pos, current_player_pos, current_player_pos }; //initialize a new array of positions for checking each value 
	
	//set up these new positions 
	new_pos[0].row -= 1; //up
	new_pos[1].row += 1; //down
	new_pos[2].col += 1; //right
	new_pos[3].col -= 1; //left
	
	for(int i = 0; i < 4; i++){ //for every position...
			
			//if player is an enemy...
			if(p->is_human() == false){
				//if the position isn't a wall, an exit, or an enemy, and isn't outside the bounds of the board...	
				//Note - even though the rules say enemies can lose turns if they run into each other, I found that this messed up the AI, so I just made it so that they can't run into each other...
				if(get_square_value(new_pos[i]) != SquareType::Wall && 0<=new_pos[i].row && new_pos[i].row<4 && 0<=new_pos[i].col && new_pos[i].col<4 && get_square_value(new_pos[i]) != SquareType::Exit && get_square_value(new_pos[i]) != SquareType::Enemy){ 
					avaliable_positions.push_back(new_pos[i]); //we've found a valid position - append this position to the list of positions 
				}
			}
		
			//if player is a human 
			else if(p->is_human()){
				//if the position isn't a wall and isn't outside the bounds of the board...	
				if(get_square_value(new_pos[i]) != SquareType::Wall && 0<=new_pos[i].row && new_pos[i].row<4 && 0<=new_pos[i].col && new_pos[i].col<4){ 
					avaliable_positions.push_back(new_pos[i]); //we've found a valid position - append this position to the list of positions 
				}
			}
	}
	return avaliable_positions; //returns ALL avaliable positions the player can move 
}

/**
	Move a player to a new position on the board. Return true if they moved successfully, false otherwise.
	@player is the player passed-in
	@pos is the DESIRED position - NOT the player's position
*/
bool Board::MovePlayer(Player *p, Position pos){
	std::vector<Position> possible_moves = GetMoves(p);  //a vector of the possible positions for the player 
	bool can_move = false;  //by default, the player won't be allowed to move anywhere... 
	
	for(unsigned int i = 0; i <= possible_moves.size(); i++){ //check each Position value in the vector of all moves to see if any are valid...
		if(pos == possible_moves[i]){ //if any allowed-position matches the desired one, then the player can move 			
			
			//change the player's current square to empty 
			Position current_position = p->get_position();
			SetSquareValue(current_position, SquareType::Empty);

			
			//TODO: MAKE SURE ENEMIES CAN'T GET TO EXIT 
			if(get_square_value(pos) == SquareType::Treasure){
				p -> ChangePoints(100); //give 100 points to the player for finding the treassure 
				can_move = true;
			}
			
			if(get_square_value(pos) == SquareType::Enemy){ 
				SetSquareValue(pos, SquareType::Enemy); //basically, just replace the player with an enemy, then the IsGameOver() will handle the rest
			}
			else{//set new player position	
					if(p->is_human()){//if player is a human 
						SetSquareValue(pos, SquareType::Human);
					}
					else{//if player is an enemy 
						SetSquareValue(pos, SquareType::Enemy);
					}
					p -> SetPosition(pos); //actually move the player to this new requested position 	
				can_move = true; //finally, the player has moved successfully!
			}
		}
	}
	return can_move; 
}

/**
	 Get the square type of the exit square
*/
SquareType Board::GetExitOccupant(){
	SquareType tmp_sq_type; 
	if(arr_[3][3] == SquareType::Human){ 
		tmp_sq_type = SquareType::Human; 
	}
	else if(arr_[3][3] == SquareType::Exit){ 
		tmp_sq_type = SquareType::Exit; 
	}
	return tmp_sq_type; 
}

/**
	Constructor for Maze 
*/
Maze::Maze(){
	int num_enemies = 0; //by default, start with 0 enemies  
	
	Board *board1 = new Board();
	board_ = board1;
		
	std::string player_name; 
	
	std::cout<<"Enter a name for the main player: "; 
	std::cin>>player_name; 
	std::cout<<std::endl; 
	
	num_enemies = 2; //start with 2 enemies, but this can be changed later
	
	turn_count_ = 10; //the player has 10 turns to get through the full maze 
	

	Player p1(player_name, true); //initliaze the player with their proper name the player chose, and say they're human 
	
	NewGame(&p1, num_enemies);
} 

	// initialize a new game, given one human player and 
	// a number of enemies to generate
void Maze::NewGame(Player *human, const int enemies){	
	players_.push_back(human); //push the human player into the vector of players so that we can access them all later  
	current_player_index_= 0; //0 represents the index of the player 
	
	
	//Create Enemies 
	Player enemy1("Enemy1", false); 
	Position enemy1_pos = {2, 0}; 
	enemy1.SetPosition(enemy1_pos);
	players_.push_back(&enemy1);
	board_->SetSquareValue(enemy1_pos, SquareType::Enemy); 
	
	Player enemy2("Enemy2", false); 
	Position enemy2_pos = {2, 1}; 
	enemy2.SetPosition(enemy2_pos);
	players_.push_back(&enemy2);
	board_->SetSquareValue(enemy2_pos, SquareType::Enemy); 
	
	//NOTE - I know this is a bit redunant, but my original implementation for initializing enemies using a nice for loop, 
	//however, there were problems with variable names (same enemy would get placed twice) and/or memory problems
	//and trying to set up the enemies as an array seemed to be more tedious and wasteful 
	
	//PRINT THE BOARD 
	while(!IsGameOver()){	
		for(int x = 0; x < 4; x++){ 
			for (int y = 0; y < 4; y++){ 
				Position pos = {x, y}; //declare a new temporary position that changes for each iteration of the loop, thus becoming every position 
				
				SquareType current_square = board_->get_square_value(pos);
	
				//display the current board using a swtich statement 
				switch(current_square){
					case SquareType::Human :std::cout<<SquareTypeStringify(SquareType::Human);  break; 
					case SquareType::Enemy :std::cout<<SquareTypeStringify(SquareType::Enemy);  break; 						
					case SquareType::Wall :std::cout<<SquareTypeStringify(SquareType::Wall);  break; 
					case SquareType::Exit :std::cout<<SquareTypeStringify(SquareType::Exit);  break; 
					case SquareType::Treasure :std::cout<<SquareTypeStringify(SquareType::Treasure);  break; 
					case SquareType::Empty :std::cout<<SquareTypeStringify(SquareType::Empty);  break; 
				}
					
			}
			std::cout<<std::endl; 
		}
		std::cout<<std::endl; 
		TakeTurn(players_[current_player_index_]);
		GetNextPlayer(); 
	}
	std::cout<< GenerateReport() << std::endl; 

}	

/**
	TakeTurn has the given player take their turn
	Adapted for use with AI 
*/
void Maze::TakeTurn(Player *p){
	
	//display and then reduce the number of turns left, but only if the human is playing 
	//this is up here for formatting purposes 
	if(p->is_human()){
		turn_count_--; 
		std::cout<<"You have " << turn_count_ << " turns left to get to the end of the maze" << std::endl; 
	}
	
	
	Position current_player_pos = p -> get_position(); //declare the player's position so we don't have to keep accessing it in the loops
	std::vector<Position> list_of_positions = board_->GetMoves(p); //a vector that will be filled with possible positions the player can move  
	
	std::cout<< p -> Stringify(); 
	std::cout<<" and can go: ";
	for(unsigned int i = 0; i < list_of_positions.size(); i++){
		std::cout<< p->ToRelativePosition(list_of_positions[i]) << "  "; 
	}
	std::cout<<std::endl;
	
	//IF THE PLAYER IS A HUMAN...
	if(p ->is_human()){
		bool correct_input = false; //will turn to true once the player has entered a correct input 

		std::string input = ""; 

		while(correct_input == false){ //while the player hasn't entered a correct input...
		std::cout<<"Enter a direction to move: ";
		std::cin>>input;
		bool input_matches_list = ValidMove(p, input, list_of_positions); //checks if the input actually matches the list of valid inputs 
			
			//make sure the input matches the list before doing anything else 
			if(input_matches_list == true){	//figure out if the player's directions match a real one, change the position based on this...
				
				//now determine where the player should be moved...
				if(input == "UP"){
					correct_input = true;
					current_player_pos.row -= 1;
				}
				if(input == "DOWN"){
					correct_input = true;
					current_player_pos.row += 1;
				}
				if(input == "LEFT"){
					correct_input = true;
					current_player_pos.col -= 1;
				}		
				if(input == "RIGHT"){
					correct_input = true;
					current_player_pos.col += 1;
				}
				
				//now we assume they've entered the correct input, so move the player! 
				correct_input = true; 
				board_->MovePlayer(p, current_player_pos); 
				break; 
			}

			//otherwise, they messed up, go back  
			else{
				std::cout<<"Not a valid move! Enter a valid direction in ALL CAPS";
				std::cout<<std::endl; 				
			}

		}
	
		if(board_->get_square_value(current_player_pos) == SquareType::Treasure){ //once the player encounters treasure
			//increase player's points
			p->ChangePoints(100);
		}
		if(p->is_human()){
			if(board_->get_square_value(current_player_pos) == SquareType::Enemy){ //once the player encounters an enemy 
				board_->SetSquareValue(current_player_pos, SquareType::Enemy); //set the Square to the enemy's square, "killing" the human 
			}
		}
	}
	
	//IF THE PLAYER IS AN ENEMY...
	else{
		//This function will handle the AI input
		AIEnemyTurn(p, current_player_pos, list_of_positions); 
	}
}

/**
	check if the string input passed in matches the possiblePositions, return true if so 
	This function is designed to make sure an input is valid based on the data gathered by previous functions 
	
	Originally designed for player input, repurposed for the AI functionality as well...
	
	@player is any player passed in, used for determing the valid moves based on it's position
	@move is just a string input
	@list of positions is literally just list of positions from the TakeTurn function 

*/
bool Maze::ValidMove(Player *p, std::string move, std::vector<Position> &list_of_positions){
	bool matched = false; 
	
	//for all positions is the list_of_positions... 
	for(unsigned int i = 0; i < list_of_positions.size(); i++){
		if(p->ToRelativePosition(list_of_positions[i]) == move){ //if the move matches the list of positions...
			matched = true; 
		} 
	}
	return matched; 
}

/**
	My own function to move the enemy AI across the board without user input 
	Certain enemies have different behaviors depending on which one they are 
	@human is the human player (really, only used for calculating position)
	@enemy is the enemy player who is going to move 
*/
void Maze::AIEnemyTurn(Player *p, Position current_enemy_pos, std::vector<Position> &list_of_positions){
	
	Position human_pos = players_[0] -> get_position(); //the human's current position on the board
	
	//bools to determine whether a move is valid. Limits the amount of function-calls later on 
	bool valid_up = ValidMove(p, "UP", list_of_positions);
	bool valid_down = ValidMove(p, "DOWN", list_of_positions);
	bool valid_left = ValidMove(p, "LEFT", list_of_positions);
	bool valid_right = ValidMove(p, "RIGHT", list_of_positions);
		
	//enemy 1 will seek out the human, but only horizontally  
	if(p->get_name() == "Enemy1"){
		//if the enemy is to the left or on the same column as the player, move right... 
		if((current_enemy_pos.col < human_pos.col  || current_enemy_pos.col == human_pos.col) && valid_right){ //note - also checking if its a valid move... 
			current_enemy_pos.col += 1; //move right
		}
		//otherwise, move left 
		else if(current_enemy_pos.col > human_pos.col && valid_left){
			current_enemy_pos.col -= 1; //move left 
		}
		//otherwise, the enemy just won't move... 
	}
	
	
	//enemy 2 will seek out the human, but only vertically  
	if(p->get_name() == "Enemy2"){
		if(current_enemy_pos.row < human_pos.row && valid_up){
			current_enemy_pos.row -= 1;
		}
		else if((current_enemy_pos.row > human_pos.row || current_enemy_pos.row == human_pos.row) && valid_down){
			current_enemy_pos.row += 1;
		}
	}
	
	//any more enemies will just move in random directions 
	else{
		if((rand() % 1) == 1){ //randomly pick either row or column to modify (this value with either randomly return true or false)
			if(valid_up && valid_down){
				current_enemy_pos.row += (rand() % 2) -1; //will either be -1, 0, 1 
			}
		}
		else{
			if(valid_left && valid_right){ 
				current_enemy_pos.col += (rand() % 2) -1; //will either be -1, 0, 1 
			}
		}
	}
	
	
	//once we've determined which way the enemy should move, actually move them on the board...
	board_->MovePlayer(p, current_enemy_pos); 

	//if the enemy encounters treasure
	if(board_->get_square_value(current_enemy_pos) == SquareType::Treasure){ 
		//increase player's points
		p->ChangePoints(100);
	}
	
	//if the enemy encounters a human
	if(board_->get_square_value(current_enemy_pos) == SquareType::Human){ 
		board_->SetSquareValue(current_enemy_pos, SquareType::Enemy); //set the Square to the enemy's square, "killing" the human 
	}

}

/**
	Get the next player in turn order, using the current_player_index
*/
Player * Maze::GetNextPlayer(){  
	current_player_index_++; 
	
	if(current_player_index_ >= players_.size()){
		current_player_index_ = 0; 
	}
	
	return players_[current_player_index_];
}


/**
	return true iff the human made it to the exit OR
	the player gets a game over as a result of running out of turns, or gets eaten by an enemy 
	
*/	
bool Maze::IsGameOver(){
	
	//if the human finally made it to the exit... 
	if(board_->GetExitOccupant() == SquareType::Human){
		std::cout<<std::endl;
		std::cout<<"You got to the exit! Congrats!" <<std::endl; 
		return true;
	}
	
	//check if the player has run out of turns, and end the game if they have 
	if(turn_count_ == 0){
		std::cout<<"Oh no! You ran out of turns!"<<std::endl; 
		return true; 
	}
	
	//check if there's still a player on the board 
	for(int x = 0; x < 4; x++){
		for(int y = 0; y < 4; y++){
			Position temp_pos = {x,y};//temporary x and y position, iterates thru all possible positions on the board
			SquareType temp_sq = board_->get_square_value(temp_pos); 
			
			//if we've found a player on the board...  
			if(temp_sq == SquareType::Human){
				return false; // then keep playing, player isn't dead
			}
		}
	}
	
	//function will only reach this point if there's no player left on the board (e.g., the player has been eaten by an enemy )
	std::cout<<"Oh no! You got eaten by an enemy!" << std::endl; 
	return true; 
}

std::string Maze::GenerateReport(){
	std::cout<<std::endl; 
	std::cout<<"** GAME OVER ** " << std::endl; 
	for(unsigned int i = 0; i < players_.size(); i++){
		std::cout<<" - " << players_[i]->get_name() << " finished with " <<  players_[i]->get_points() << " points"<< std::endl; 
	}
	return " - - - Thank you for playing - - - "; 
}
