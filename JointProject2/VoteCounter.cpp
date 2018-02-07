//Christian Bradford
//C00223037
//Joint Assignment 2 

#include "VoteCounter.h"

void VoteCounter::Start()
{
	char answer = 0;
	while (true)
	{
		std::cout << "Would you like to do a manual process or load a file? (m | l) ";
		std::cin >> answer;
		if (answer == 'l')
		{
			std::string filename = "../Data/Vote_Results.voteCounter";
			StartVotingFile(filename);
			break;
		}
		else if (answer == 'm')
		{
			std::list<Candidate> candidates = InitManualProcess();
			StartVotingManual(candidates);
			break;
		}
	}
}
void VoteCounter::StartVotingManual(const std::list<Candidate> candidates)
{
	std::list<BallotPaper> ballotPapers;
	std::list<Candidate> currentCandidates;
	int numVoters = 0;
	int currentPick;
	bool answer = false;
	std::cout << std::endl << "Lets start the voting process!" << std::endl;
	while (answer == false)
	{
		BallotPaper *currentBallotPaper = new BallotPaper();
		currentPick = 0;
		++numVoters;
		currentCandidates = candidates;
		while (currentCandidates.size() >= 1)
		{
			PrintOutAllCandidates(currentCandidates);
			currentPick++;
			int index = 0;
			while (index < 1 || index > currentCandidates.size())
			{
				std::cout << "Voter #: " << numVoters << " Current Pick: " << currentPick << " (Pick The Candidate Number)? ";
				index = CheckForValidNumberInput();
			}
			std::list<Candidate>::iterator it1 = currentCandidates.begin();
			std::advance(it1, --index);
			currentBallotPaper->setPreference(currentPick, *it1);
			currentCandidates.erase(it1);
		}
		ballotPapers.push_back(*currentBallotPaper);
		delete currentBallotPaper;
		std::cout << std::endl;
		answer = AskForInput("Would you like to add another Voter?");
	}
	FigureOutWhoWon(ballotPapers, candidates);
}
void VoteCounter::FigureOutWhoWon(const std::list<BallotPaper> ballotPapers, const std::list<Candidate> &candidates)
{
	int round = 0;
	std::list<CandidateVotes> totalVotes;
	//Candidates and their votes
	totalVotes = CountVotes(candidates, ballotPapers);
	//Print Progress
	PrintOutVotersAndTheirPreferences(ballotPapers, candidates.size());
	while (totalVotes.size() > 1)
	{
		//Sort out the list in ascending order
		totalVotes = SortDesending(totalVotes);
		//Print out the Candidates names and the number of votes that they have
		PrintOutCandidatesAndThierVotes(totalVotes, round);
		//Find The candidate(s) in last place
		std::list<CandidateVotes> lowestVotes = FindAllTheLowestVotes(totalVotes);
		CandidateVotes loserCandidate;
		if (lowestVotes.size() > 1)
		{
			PrintOutTiedCandidates(lowestVotes);
			loserCandidate = FindTheLoserCandidate(lowestVotes);
		}
		else
			loserCandidate = *lowestVotes.cbegin();
		//Print out the lost Candidate
		std::cout << "Candidate " << loserCandidate.c.GetName() << " has lost the race... " << std::endl;
		//Find out where the votes goes too
		TransferVotes(loserCandidate, totalVotes);
		//Get rid of the loser Candidate from the list of votes
		std::list<CandidateVotes> newList;
		for (auto cv : totalVotes)
		{
			if (cv.c != loserCandidate.c)
				newList.push_back(cv);
		}
		totalVotes = newList;
		round++;
	}
	PrintOutCandidatesAndThierVotes(totalVotes, round);
	std::cout << "The winner is Candidate: " << (totalVotes.begin())->c.GetName() << std::endl;
}
void VoteCounter::TransferVotes(CandidateVotes loserCandidate, std::list<CandidateVotes> &totalVotes)
{
	std::cout << "The vote(s) that went to Candidate " << loserCandidate.c.GetName() << " is going to:" << std::endl;
	if (loserCandidate.votes.size() < 1)
		std::cout << "There was no votes for Candidate " << loserCandidate.c.GetName() << std::endl;
	else
	{
		std::list<BallotPaper> transferBallotPapers;
		for (auto bp : loserCandidate.votes)
		{
			//You can take the round number and add one to get to the round preference since round will always be less then total starting Candidates
			Candidate tmp;
			int prefence = 2; //Start off with the second choice
			bool exists = false;
			while (exists == false)
			{
				tmp = bp.getPreference(prefence);
				for (auto cv : totalVotes)
				{
					if (cv.c == tmp && cv.c != loserCandidate.c)
					{
						exists = true;
						break;
					}
				}
				prefence++;
			}
			std::cout << "Candidate: " << tmp.GetName() << std::endl;
			for (std::list<CandidateVotes>::iterator it = totalVotes.begin(); it != totalVotes.end(); ++it)
			{
				if (it->c == tmp)
				{
					it->votes.push_back(bp);
					break;
				}
			}
		}
	}
}
const std::list<CandidateVotes> VoteCounter::CountVotes(const std::list<Candidate> &candidates, const std::list<BallotPaper> &ballotPapers)
{
	std::list<CandidateVotes> totalVotes;
	//Set up the list of the CandidateVote Structure
	for (std::list<Candidate>::const_iterator it = candidates.cbegin(); it != candidates.cend(); ++it)
	{
		CandidateVotes tmp;
		Candidate c = Candidate(*it);
		tmp.c = c;
		totalVotes.push_back(tmp);
	}
	//Count the votes and add it to the correct candidate
	for (auto bp : ballotPapers)
	{
		Candidate first = bp.getPreference(1);
		for (std::list<CandidateVotes>::iterator it = totalVotes.begin(); it != totalVotes.end(); ++it)
		{
			if (it->c.GetName() == first.GetName())
			{
				it->votes.push_back(bp);
				break;
			}
		}
	}
	return totalVotes;
}
std::list<CandidateVotes> VoteCounter::FindAllTheLowestVotes(const std::list<CandidateVotes> &votes)
{
	//The list can have mulitple ties so add all the lowest counts to another list
	std::list<CandidateVotes> lowestVotes;
	int lowestVoteCount = -1;
	//Find the lowestVoteCount 
	for (std::list<CandidateVotes>::const_iterator it = votes.cbegin(); it != votes.cend(); ++it)
	{
		if (it->votes.size() < lowestVoteCount)
			lowestVoteCount = it->votes.size();
	}
	//Add to the return list if it matches the lowest vote count
	for (std::list<CandidateVotes>::const_iterator it = votes.cbegin(); it != votes.cend(); ++it)
	{
		if (it->votes.size() == lowestVoteCount)
			lowestVotes.push_back(*it);
	}
	return lowestVotes;
}
void VoteCounter::PrintOutTiedCandidates(const std::list<CandidateVotes> &votes)
{
	std::string candidateNames;
	int stopIndex = votes.size() - 1;
	int currentIndex = 0;
	for (auto cv : votes)
	{
		candidateNames += cv.c.GetName();
		if (currentIndex < stopIndex)
			candidateNames += ", ";
		currentIndex++;
	}
	std::cout << "These Candidates are tied: " << candidateNames << ". Randomly selecting which one is kicked out of the race...." << std::endl;
}
CandidateVotes VoteCounter::FindTheLoserCandidate(std::list<CandidateVotes> &votes)
{
	int listIndex = (rand() % votes.size()); // rand % starts at one and the indexing starts at one
	std::list<CandidateVotes>::const_iterator it1 = votes.cbegin();
	std::advance(it1, listIndex);
	return *it1;
}
void VoteCounter::PrintOutCandidatesAndThierVotes(const std::list<CandidateVotes> &votes, int round)
{
	std::cout << std::endl << "Printing out round # " << round << std::endl;
	for (auto v : votes)
		std::cout << "Candidate " << v.c.GetName() << " has " << v.votes.size() << " votes" << std::endl;
}
void VoteCounter::PrintOutVotersAndTheirPreferences(std::list<BallotPaper> ballotPapers, int numCandidates)
{
	std::cout << "Printing the voters and their preference of highest to lowest." << std::endl;
	int numVoter = 0;
	for (auto bp : ballotPapers)
	{
		std::cout << "Voter #" << ++numVoter << ": ";
		for (int i = 0; i < numCandidates; i++)
		{
			std::cout << bp.getPreference(i + 1).GetName();
			if (i + 1 < numCandidates)
				std::cout << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::list<Candidate> VoteCounter::InitManualProcess()
{
	int count = 0;
	bool answer = false;
	std::list<Candidate> candidates;
	while (answer == false)
	{
		std::string name;
		std::string party;
		std::cout << "What is the name of Candidate #" << ++count << "? ";
		std::cin >> name;
		std::cout << "What is the party of Candidate #" << count << "? ";
		std::cin >> party;
		Candidate *tmp = new Candidate(name, party);
		candidates.push_back(*tmp);
		std::cout << std::endl;
		answer = AskForInput("Would you like to add another Candidate?");
	}
	return candidates;
}

void VoteCounter::PrintOutAllCandidates(std::list<Candidate> candidates)
{
	int count = 0;
	for (auto c : candidates)
		std::cout << "Candidate # " << ++count << " Name: " << c.GetName() << " Party: " << c.GetParty() << std::endl;
}
std::list<CandidateVotes> VoteCounter::SortDesending(const std::list<CandidateVotes> &totalVotes)
{
	std::list<CandidateVotes> returnList;
	bool added = false;
	for (auto tv : totalVotes)
	{
		bool added = false;
		if (returnList.size() == 0)
		{
			returnList.push_front(tv);
			continue;
		}
		std::list<CandidateVotes>::const_iterator it1 = returnList.cbegin();
		while (it1 != returnList.cend())
		{
			if (it1->votes.size() <= tv.votes.size())
			{
				returnList.insert(it1, tv);
				added = true;
				break;
			}
			std::advance(it1, 1);
		}
		if (added == false) //means thats the tv object is the largest in the list so put it at the end
			returnList.push_back(tv);
	}
	return returnList;
}
int VoteCounter::CheckForValidNumberInput()
{
	int returnValue = 0;
	while (!(std::cin >> returnValue))
	{
		std::cin.clear();
		std::cin.ignore(999, '\n');
		std::cout << "Please type in a number!!" << std::endl;
		std::cout << "Type in a number: ";
	}
	return returnValue;
}
bool VoteCounter::AskForInput(std::string message)
{
	std::cout << std::endl;
	std::cout << message << " (y|n): ";
	char returnValue = CheckForValidQuitInput();
	std::cin.clear();
	std::cin.ignore(999, '\n');
	std::cout << std::endl;
	if (returnValue == 'y')
		return false;
	return true;
}
char VoteCounter::CheckForValidQuitInput()
{
	char returnValue = 0;
	bool validInput = false;
	bool failedFlag = false;
	while (!validInput)
	{
		std::cin.clear();
		std::cin.sync();
		if (failedFlag)
			std::cout << "Type in a answer: ";
		std::cin >> returnValue;
		if (returnValue == 'y' || returnValue == 'n')
			validInput = true;
		else
		{
			returnValue = 0;
			failedFlag = true;
		}
	}
	return returnValue;
}
void VoteCounter::StartVotingFile(std::string fileName)
{
	char ignoreCharacter = '#';
	std::string seperateCharacter = "";
	bool isCandidates = true;
	std::string line;
	std::list<std::string> listOfInputs = {};
	std::list<std::string> candidatesString = {};
	std::list<std::string> votersString = {};
	std::ifstream myfile(fileName);
	try
	{
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				if (line[0] != ignoreCharacter)
				{
					if (line == seperateCharacter)
					{
						if (isCandidates)
						{
							isCandidates = false;
							candidatesString = listOfInputs;
							listOfInputs = {};
						}
					}
					else
						listOfInputs.push_back(line);
				}
			}
			myfile.close();
			votersString = listOfInputs;
		}
		else
		{
			throw FileReadError;
		}
		std::list<Candidate> candidates = ConvertToCandidates(candidatesString);
		if (candidates.size() <= 0)
			throw CandidatesError;
		std::list<BallotPaper> voters = ConvertToBallotPapers(votersString, candidates);
		if (voters.size() <= 0)
			throw VotersError;
		FigureOutWhoWon(voters, candidates);
	}
	catch (ERROR_CODES error)
	{
		switch (error)
		{
		case CandidatesError:
			std::cout << "The file is not set up properly.  Please fix the Candidates and try again!" << std::endl;
			break;
		case VotersError:
			std::cout << "The file is not set up properly.  Please fix the Votes and try again!" << std::endl;
			break;
		case FileReadError:
			std::cout << "Can not read the file.  Please fix it and try again!" << std::endl;
			break;
		default:
			break;
		}
		return;
	}
}
std::list<Candidate> VoteCounter::ConvertToCandidates(std::list<std::string> candidatesString)
{
	/*
		Each line will be set as NAME,PARTY for the Candidate
	*/
	std::list<Candidate> returnList;
	bool isCreated = false;
	Candidate tmp;
	for (auto line : candidatesString)
	{
		std::stringstream ss(line);
		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ',');
			if (isCreated == false)
			{
				tmp = {};
				tmp.SetName(substr);
				isCreated = true;
			}
			else
			{
				tmp.SetParty(substr);
				returnList.push_back(tmp);
				isCreated = false;
			}
		}
	}
	return returnList;
}
std::list<BallotPaper> VoteCounter::ConvertToBallotPapers(std::list<std::string> votesString, const std::list<Candidate> &candidates)
{
	/*
		Each line will be set as firstPrefence,SecondPrefenece,ThirdPrefenece 
		Choosing these numbers are based on the index of the candidates listed in the file
	*/
	std::list<BallotPaper> returnList = {};
	try
	{
		std::list<Candidate>::const_iterator it1;
		for (auto line : votesString)
		{
			std::stringstream ss(line);
			int i;
			int preference = 0;
			BallotPaper tmp;
			while (ss >> i)
			{
				it1 = candidates.cbegin();
				std::advance(it1, i - 1);
				tmp.setPreference(++preference, *it1);
				if (ss.peek() == ',')
					ss.ignore();
			}
			returnList.push_back(tmp);
		}
		return returnList;
	}
	catch (const std::exception&)
	{
		return returnList;
	}
}