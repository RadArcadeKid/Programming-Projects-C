#ifndef _TEXT_UI_H_
#define _TEXT_UI_H_

#include "Election.h"
#include <string>
/**
  CREATED BY JAKE HENSON
	Homework 3
	TextUI.h - The header file for the TextUI class which determines player interaction.
*/

class TextUI{
public:
  TextUI(); //starts the game
  void SetParties(); //sets up the all_parties_ string vector

  void Registration(std::string election_type); //registers candidates and sends them on their way!

  void Campaign_Loop(std::string election_type, Election elec); //allows for the campaign loop of the game to begin
  void Campaign_Loop(std::string election_type, RepresentativeElection elec); //override operator


private:
  std::vector<Party> all_parties_;
};


#endif  // _ELECTORAL_MAP_H_
