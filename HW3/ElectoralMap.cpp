/**
DO NOT REPRODUCE WITHOUT CREDIT TO THE ORIGINAL AUTHOR
CREATED BY JAKE HENSON
  for	Homework 3
	ElectoralMap.cpp - Serves as the implentation for the map for the election, Districts
*/
#include "ElectoralMap.h"


/**
  PartyStringify converst a party object to a string
  @params - takes in a party object
  @returns a corrosponding string
*/
std::string PartyStringify(Party part_e){
  std::string party_string;
  switch(part_e) {
    case Party::None : party_string = "None"; break;
    case Party::One : party_string ="One"; break;
    case Party::Two : party_string ="Two"; break;
    case Party::Three : party_string ="Three"; break;
  }

  return party_string;
}


/**
  Initialize a single instance of the ElectoralMap; Set All Districts
  @params - none;
  @returns - none;
*/
ElectoralMap::ElectoralMap() {
    srand(time(0)); //seed random number;
    //initilaize Districts here
    District d0;
    District d1;
    District d2;
    //
    d0.SetID(1); //tell the district what its ID is....
    district_map_.insert({1, d0}); //place this district into the map
    d1.SetID(2); //tell the district what its ID is....
    district_map_.insert({2, d1}); //place this district into the map
    d2.SetID(3); //tell the district what its ID is....
    district_map_.insert({3, d2}); //place this district into the map
}

void ElectoralMap::Campaign_Tally(Candidate cand){
  //check to see how many people in each district are alligned with the candidate
  for(auto& it: district_map_){ //for every element in the map
    std::cout<< it.first << ". District: " << it.second.get_ID() << std::endl;
    std::cout<< "   " << cand.name_ << ": " << it.second.get_num_constituent_per_party(cand.party_affliation_) << std::endl;
  }

}

void ElectoralMap::GoToDistrict(Candidate cand, int district_id){
  //retrieve the district that this candidate wants to campaign in
  std::cout<< cand.id_ << " is campaigning in District " << district_id <<std::endl;
  //get_district(district_id).is_campaigning_in_district(cand);
  district_map_.at(district_id).is_campaigning_in_district(cand);
}

/**
  Initialize a single instance of the ElectoralMap; Set All Districts
  @params - takes in the id of the requested district
  @returns - returns the district
*/
District ElectoralMap::get_district(int id){
    return district_map_.find(id)->second; //return the district map at the specific ID
}

District::District(){
  square_miles_ = rand() % 5 + 29; //set random area bettween 5 and 29 miles
  //num_constituents_ = rand() % 9; //set a random number of constituents between 0 and 9

  //map the three parties with count 0;
  constituents_.insert({Party::None, rand() % 9});
  constituents_.insert({Party::One, rand() % 9});
  constituents_.insert({Party::Two, rand() % 9});
  constituents_.insert({Party::Three, rand() % 9});
}

void District::is_campaigning_in_district(Candidate cand){
  //determine how likely the probably of winning people over are!
  double top = ((get_num_constituent_per_party(cand.party_affliation_)+1)*2); //easier to just sort out the top of the probablility here

  double pSuccess = ( ( top / get_num_constituent_NOT_in_party(cand.party_affliation_) ) * ( top / square_miles_ )  );
  double pExSuccess = pSuccess * 0.1;

  std::cout<< "Changes to convert:" << pSuccess << std::endl;
  std::cout<< "Chances to convert from another party: " << pExSuccess << std::endl;
  std::cout<< std::endl;
}

/**
  Picks a party based on the integer passed in, returns the corrosponding party
*/
Party District::PartyPicker(int rn){
  switch(rn){
    case 0 : return Party::None; break;
    case 1 : return Party::One; break;
    case 2 : return Party::Two; break;
    case 3 : return Party::Three; break;
  }
}


/**
  MajorityParty will calculate the most popular party in a district
  @returns this party
*/
Party District::MajorityParty(){
  int num_greatest = 0;
  Party major;
  for(auto& it: constituents_){
    if(it.second > num_greatest){
      major = it.first;
    }
  }
  return major;
}
/**
  castVotes will cast all of the votes for the constituents_ in the district!
*/
void District::castVotes(){
  Party majority_party = MajorityParty(); //get the party with the highest number of constituents_


  //let constituents_ in None vote first...
  for(int i = 0; i < constituents_.at(Party::None); i++){
    int vote = rand() % 100 + 1;
    if(vote <= 70){
      ConvertConstituent(Party::None, majority_party); //convert to majority party
    }
    else{
      int rand_party = rand() % 3 + 1; //pick a random value
      ConvertConstituent(Party::None, PartyPicker(rand_party));  //vote randomly
    }
  }

  //then let the constituents in the other parties vote.

}

/**
  ConvertConstituent converts a constituent from party_away to party_to
  Used for the actual conversion of each member
  @params - takes in
*/
void District::ConvertConstituent(Party party_away, Party party_to){
    constituents_.find(party_away)->second -= 1;//decrement the away party
    constituents_.find(party_to)->second += 1;//increment the to party
}

/**
  Returns the number of constituents_ who are NOT in the passed-in party
  Useful for probablility
  @params - takes in the undesired party
  @returns - returns the sum of all of the constituents not in the undesired party
*/
int District::get_num_constituent_NOT_in_party(Party not_p){
    int sum_of_the_rest_of_parties = 0;
    for(auto& it: constituents_){
      if(it.first != not_p && it.first != Party::None){ //if this party is NOT the one we passed in
          sum_of_the_rest_of_parties += it.second;
      }
    }
    return sum_of_the_rest_of_parties;
}
