/**
DO NOT REPRODUCE WITHOUT CREDIT TO THE ORIGINAL AUTHOR
CREATED BY JAKE HENSON
  for
	Homework 3
	Election.cpp - Serves as the implentation for the map for the election, Districts
*/
#include "Election.h"

Election::Election(){
}

/**
  Registers values passed in into a candidate which is stored in the candidates_ vector
  @params - takes in candidates' name and party_affliation
*/
void Election::RegisterCandidate(std::string name, Party party_affliation){
  Candidate can;
  can.id_ = candidates_.size()+1; //their ID will literally be just how big the vector is, so that it's automatically set to 1, 2, 3 etc.
  can.name_ = name;
  can.party_affliation_ = party_affliation;

  candidates_.push_back(can);
}

/**
  Prints all of the candidates for the initialization of the district list at the beginning of the election (easier than writing an override operator)
  @params - None
  @returns - None
*/
void Election::PrintCandidates(){
  std::cout<<"-----------------"<<std::endl;
  for(unsigned int i = 0; i < candidates_.size(); i++){
      std::cout<<candidates_.at(i).id_ << ". " << candidates_.at(i).name_ << " [Party: " << PartyStringify(candidates_.at(i).party_affliation_) <<"]" <<std::endl;
  }
  std::cout<<std::endl;
  std::cout<<std::endl;
  std::cout<<std::endl;
  //prints out like:
  //---------------------------
  // 1: Ann [Party: one]
  // 2: Bob [Party: two]
  // 3: Charlie [Party: three]
}

void Election::Campaign_Candindate(int candidate_id){
  std::string desired_district;

  ElectoralMap &elecmap=ElectoralMap::GetInstance(); //let's get that singleton!
  std::cout << elecmap;

  std::cout << "Which district should " << candidates_.at(candidate_id).name_ << " campaign in? (id)";
  std::cin>> desired_district; //district_num;
  elecmap.GoToDistrict(candidates_.at(candidate_id), stoi(desired_district));

  //if they've won:
  // elecmap.Campaign_Tally(candidates_.at(candidate_id)); //display whay the candidate has in this Campaign_Tally

}
