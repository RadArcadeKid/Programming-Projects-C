#ifndef _ELECTION_H_
#define _ELECTION_H_

#include "ElectoralMap.h"
/**
DO NOT REPRODUCE WITHOUT CREDIT TO THE ORIGINAL AUTHOR
CREATED BY JAKE HENSON
  for	Homework 3
	Election.h - Serves as a map for the election
*/

class Election{
public:
  Election();

  void RegisterCandidate(std::string name, Party party_affliation_);

  void PrintCandidates();//prints out the list of Candidates + ID's when called!

  void Campaign_Candindate(int candidate_id);
  //int Campaign(); //chose which district?
  //figure out voting system for basic election...

  std::vector<Candidate> get_candidates_vector() {return candidates_; } //returns candidates for TextUI to use!


private:
  std::vector<Candidate> candidates_; //a vector to store all the candidates in...
};

class RepresentativeElection : Election {
public:

 void Campaign_Candindate_Representative(int candidate_id);
private:
};

#endif  // _ELECTION_H_
