#ifndef _ELECTORAL_MAP_H_
#define _ELECTORAL_MAP_H_

/**
DO NOT REPRODUCE WITHOUT CREDIT TO THE ORIGINAL AUTHOR
CREATED BY JAKE HENSON
  for	Homework 3
	ElectoralMap.h - Serves as a map for the election
*/

#include <iostream> //neeed to stream objects in and out
#include <vector> //include vectors to use them later for data storage
#include <map> //include maps to store data in an ElectoralMap
#include <string> //include a string value
#include <ctime> //for use with running random and generating random seeds (used with rand() functionality)

enum class Party{None, One, Two, Three};
static const int num_parties = 4; //be sure to only include 2, not one for None party
//
//note - if you want to change the number of parties, you can update parties enum BUT ALSO
//must update num_parties. This is really just because enum classes don't have an easy way of telling
//how large they are like vectors or strings...


struct Candidate{
  int id_;
  std::string name_;
  Party party_affliation_;
};



std::string PartyStringify(Party part); //a helper stringify for Party data types - declared as a free function to allow for all classes to have access to it!

class District{
public:

  District(); //should initialize number of constituents

  void SetID(int id){ id_ = id; }
  int get_ID(){return id_; }

  std::map<Party, int>get_constituents(){ return constituents_; } //returns constituents_ map for use in operator

  int get_num_constituent_per_party(Party p) {return constituents_.at(p); } //returns the number of constituents associated with the party

  int get_num_constituent_NOT_in_party(Party p); //returns the constituents not in party p! (and not in none)

  void ConvertConstituent(Party a, Party b); //converts from party a to party b

  void castVotes(); //casts the votes for all the constituents in this district!

  Party PartyPicker(int rn); //asigns a party based on input

  Party MajorityParty(); //gets the majority party based on number of constituents

  void is_campaigning_in_district(Candidate cand);

  friend std::ostream &operator<<(std::ostream& output, District &district_obj){
    //output district with its ID...
      output << "District " << district_obj.id_ << ": " << std::endl;
      output << "square miles: " << district_obj.square_miles_ << std::endl;

      std::map<Party, int> constituents_temp_map = district_obj.get_constituents(); //get district map

      for(auto& it: constituents_temp_map){
          output << "[Party " << PartyStringify(it.first) << "]: " << it.second << "     ";
      }
      output << std::endl;
    return output;
  }

private:
  int square_miles_; //displays how big the district is
  int num_constituents_; //the NUMBER of constituents within the district
  std::map<Party, int> constituents_; //this is a MAP of constituents to each party
  int id_;
};


/////////////////////////////////////


class ElectoralMap {
public:

  static const int num_districts_ = 4; //can be changed without fear of breaking the code

  static ElectoralMap& GetInstance() { //static GetInstance to actually get this - prevents overlapping of instances
    // gets instantiated the first time
    static ElectoralMap instance; // guaranteed to be destroyed

    return instance;
  }

  void Campaign_Tally(Candidate can);

  std::map<int, District> get_district_map() const{
    return district_map_;
  }

  friend std::ostream &operator<<(std::ostream& output, const ElectoralMap &elecMap_obj){
    output << std::endl;
    std::map<int, District> district_temp_map = elecMap_obj.get_district_map();

    for(auto& it: district_temp_map){
        output << it.second << std::endl;
    }
    return output;
  }

  District get_district(int id); //returns the district

  void GoToDistrict(Candidate cand, int district_id);

  Candidate whoWins();

  // Delete the methods we don't want
	ElectoralMap(ElectoralMap const&) = delete; // copy constructor
	//copy makes another instance of this class, and delete it
	void operator=(ElectoralMap const&) = delete; // assignment operator

private:
  ElectoralMap(); //private constructor, make sure not to declare multiple instances!!

  std::map<int, District> district_map_; //a map to store the districts and their ID's
};



#endif  // _ELECTORAL_MAP_H_
