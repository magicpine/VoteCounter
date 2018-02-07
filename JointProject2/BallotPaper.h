//Christian Bradford
//C00223037
//Joint Assignment 2 
#pragma once
#include "Candidate.h"
#include <map>
class BallotPaper
{
public:
	BallotPaper() {}
	~BallotPaper() {}
	/*
		Sets the Perference of the Choosen Candidate
		@param preference is the preference on this ballet for a certian Candidate
		@param candidate is the Candidate
	*/
	void setPreference(int preference, Candidate candidate);
	/*	
		@param preference the preference number of the candidate 
		@return a Candidate of the peference provided
	*/
	Candidate getPreference(int preference);
private:
	std::map<int, Candidate> _candidates;
};