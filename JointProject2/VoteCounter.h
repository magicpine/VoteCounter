//Christian Bradford
//C00223037
//Joint Assignment 2 
#pragma once
#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include "Candidate.h"
#include "BallotPaper.h"

struct CandidateVotes
{
	/*
		A pointer to a Candidate
	*/
	Candidate c;
	/*
		All the ballot Papers that Are there votes
	*/
	std::list<BallotPaper> votes;
};
enum ERROR_CODES
{
	CandidatesError = 0,
	VotersError = 1,
	FileReadError = 2,
};
class VoteCounter
{
public:
	VoteCounter() {}
	~VoteCounter() {}
	/*
		Starts the VoteCounter System by asking if manual process or file process
	*/
	void Start();

private:
	/*
		Starts the voting process by voting
		@param candidates is the list of voteable candidates
	*/
	void StartVotingManual(const std::list<Candidate> candidates);
	/*
		Asks the user for all the names, and partys of the Candidates
		@return a list of Candidates that can be voted for
	*/
	std::list<Candidate> InitManualProcess();
	/*
		Print out All the Candidates
		@param candidates is a list of candidates that you would like to be printed out
	*/
	void PrintOutAllCandidates(std::list<Candidate> candidates);
	/*
		Algorthim to Figure Out who won based on a list of Ballot Papers
		@param ballotPapers is a list of Ballot Papers that contain the voting preferences
		@param candidates is the list of voteable candidates
	*/
	void FigureOutWhoWon(std::list<BallotPaper> ballotPapers, const std::list<Candidate> &candidates);
	/*
		This will take the list of Ballot papers from the Loser Candidate 
		and put the papers into the next candidate based on preference
		@param loserCandidate is the Candidate who just lost
		@param votes is the list of still running Candidates
	*/
	void TransferVotes(CandidateVotes loserCandidate, std::list<CandidateVotes> &votes);
	/*
		This counts the total number of votes for each candidate and returns a list
		@param candidates is the list of voteable candidates
		@param ballotPapers is a list of Ballot Papers that contain the voting preferences
		@return a list of CandidateVotes that contain the number of votes for each candidate
	*/
	const std::list<CandidateVotes> CountVotes(const std::list<Candidate> &candidates, const std::list<BallotPaper> &ballotPapers);
	/*
		This takes in a list of the current running Candidates and thier votes and returns a 
		list of all the lowest voted Candidates 
		@param votes is the list of still running candidates
		@return a list of CandidateVotes that contain the lowest number of votes for each candidate that tied
	*/
	std::list<CandidateVotes> FindAllTheLowestVotes(const std::list<CandidateVotes>& votes);
	/*
		Prints out the Voters and their Preferences
		@param ballotPapers is a list of Ballot Papers that you have left
		@param numCandidates is the number of total Candidates
	*/
	void PrintOutVotersAndTheirPreferences(std::list<BallotPaper> ballotPapers, int numCandidates);
	/*
		This prints out all the candidates that tied with the lowest vote
		@param votes is the list of still running candidates with the lowest votes
	*/
	void PrintOutTiedCandidates(const std::list<CandidateVotes>& votes);
	/*
		This returns the LoserCandidate that is from the lowest votes
		@param votes is the list of still running candidates with the lowest votes
		@return a CandidateVote object that is the lost Candidate
	*/
	CandidateVotes FindTheLoserCandidate(std::list<CandidateVotes>& votes);
	/*
		Prints out the Candidates and their Votes
		@param votes is the current running Candidates and thier votes
		@param round is the total round that the voting process is in
	*/
	void PrintOutCandidatesAndThierVotes(const std::list<CandidateVotes> &votes, int round);
	/*
		This takes in a list of CandidateVotes and returns the list in Descending order
		@param votes is a list of the still running Candidates
		@return a list of the same CandidateVotes list just in descending order
	*/
	std::list<CandidateVotes> SortDesending(const std::list<CandidateVotes> &totalVotes);
	/*
		This checks to see if the user entered in a real number
		@return a int processed by the user
	*/
	int CheckForValidNumberInput();
	/*
		This asks if the user is done something
		@param message is the yes or no question you would like to ask
		@return true if the answer is yes and false if the answer is no
	*/
	bool AskForInput(std::string message);
	/*
		Validates the input of the user for 'y' or 'n'
		@return a validated 'y' or 'n'
	*/
	char CheckForValidQuitInput();
	/*
		Starts the voting process from a file
		@param fileName is the relative path to the file
	*/
	void StartVotingFile(std::string fileName);
	/*
		This takes in a list of strings and coverts them into a list of Candidates
		@param candidatesString is from the file 
		@return a list of Candidates converted from strings
	*/
	std::list<Candidate> ConvertToCandidates(std::list<std::string> candidatesString);
	/*
		This takes in a list of strings and coverts them into a list of BallotPapers
		@param votesString is from the file
		@param candidates is a list of voteable candidates
		@return a list of BallotPapers converted from strings
	*/
	std::list<BallotPaper> ConvertToBallotPapers(std::list<std::string> votesString, const std::list<Candidate> &candidates);
};