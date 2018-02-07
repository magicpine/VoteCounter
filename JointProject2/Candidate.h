//Christian Bradford
//C00223037
//Joint Assignment 2 
#include<string>
#pragma once
class Candidate
{
public:
	/*
		Creates a new candidate with the name and party
		@param name of the Candidate
		@param party of the Candidate
	*/
	Candidate(std::string name, std::string party);
	Candidate() {}
	~Candidate() {}
	/*
		@return the name of the Candidate
	*/
	std::string const GetName();
	/*
		@return the party of the Candidate
	*/
	std::string GetParty();
	/*
		@param name sets the name of the Candidate
	*/
	void SetName(std::string name);
	/*
		@param party sets the party of the Candidate
	*/
	void SetParty(std::string party);
	/*
		Allows you to compare the names of the Candidates
	*/
	bool operator== (Candidate &d);
	/*
		Allows you to compare the names of the Candidates
	*/
	bool operator!= (Candidate &d);

private:
	std::string _name;
	std::string _party;
};