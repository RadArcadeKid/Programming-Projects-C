/**
CREATED BY JAKE HENSON
	Homework 3
	TextUI.cpp - Routes the player through the election, prompts the user for info
*/
#include "TextUI.h"

/**
  TectUI determines the starting game loop for the game!
  @params - none
  @returns - none, but will call other functions to continue the game
*/
TextUI::TextUI(){
  bool is_correct_input = false; //will turn to true once the player has entered a correct input

	std::string user_input = "";

	while(is_correct_input == false){ //while the player hasn't entered a correct input...
    std::cout<<"What kind of election should we have (direct or representative, 0 to stop)? ";
		std::cin>>user_input;
    if(user_input == "representative"){
        is_correct_input = true;
        Registration("representative");
        break;
    }
    if(user_input == "direct"){
        is_correct_input = true;
        Registration("direct");
        break;
    }
    if(user_input == "0"){
        is_correct_input = true;
        break; //should just exit the loop and eventually return 0 from main...
    }
    else{
        user_input = "";
        std::cout<<"NOT a valid input. Make sure your spelling is correct..." << std::endl; //bad user! try again...
        std::cout<<std::endl;
        std::cin.ignore(); //will loop back up to the top, letting the user try again...
    }
  }

    //only reaches this part when done...
}

/**
  SetParties sets all of the party objects in the string vector
*/
void TextUI::SetParties(){
  all_parties_.push_back(Party::One);
  all_parties_.push_back(Party::Two);
  all_parties_.push_back(Party::Three);
  //note - we're not adding 1 here because it's not neccessary for this specific vector to hold
}

/**
  if the player chooses they'd like a direct election, they will end up here..
  @params - none
  @returns - none
*/
void TextUI::Registration(std::string election_type){
  SetParties(); //call the setparties function to access all the parties for later
  Election dir_elec;
  //RepresentativeElection rep_elec;

  for(unsigned int i = 0; i < all_parties_.size(); i++){ //for each party

    bool is_correct_input = false; //set this to false everytime so the user must enter a valid input for every step of the way (and it will get reset for every party)
    std::string yesno = "";
    std::string user_chosen_name = "";

    while(is_correct_input == false){
        std::cout<<"Do you want to register a candidate for Party " << PartyStringify(all_parties_.at(i)) << " (y or n)? ";
        std::cin >> yesno;
        if(yesno == "y"){
          is_correct_input = true;
          //register candidate
              std::cout<<"What is their name? ";
              std::cin>> user_chosen_name;

              if(election_type == "direct"){
                dir_elec.RegisterCandidate(user_chosen_name, all_parties_.at(i));
                //set up direct election...
              }
              // if(election_type == "representative"){
              //   rep_elec.RegisterCandidate(user_chosen_name, all_parties_.at(i));
              // }
              break;
        }
        if(yesno == "n"){
          is_correct_input = true;
          //move on to to next party...
        }
        else{
          yesno = "";
          std::cout<<"Not a valid input! Try again..." << std::endl; //bad user!
          std::cout<<std::endl;
          std::cin.ignore(); //will loop back up to the top, letting the user try again...
        }
    }
  }

  //create an instance of the map
  ElectoralMap &elecmap=ElectoralMap::GetInstance();

  if(election_type == "direct"){
    std::cout << elecmap;
    dir_elec.PrintCandidates();
    Campaign_Loop(election_type, dir_elec);
  }
  if(election_type == "representative"){
    std::cout << elecmap;
    dir_elec.PrintCandidates();
    Campaign_Loop(election_type, dir_elec);
  }
}

void TextUI::Campaign_Loop(std::string election_type, Election elec){
  bool is_win = false;
  std::string campaign_person;
  int id_choice;

  while(is_win == false){ //while no candidate has won the election...
      std::cout<<"Which candidate is campaigning (id) (0 to stop)? ";
      std::cin >> campaign_person;
      id_choice = std::stoi(campaign_person);
      if(id_choice == 0){
        break;
      }
      else if(election_type == "direct"){
        elec.Campaign_Candindate(id_choice-1); //should be printing
      }
    // if(election_type == "representative"){
    //   elec.Campaign_Candindate_Representative(id_choice);
    // }


  }
}
