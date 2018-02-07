//Christian Bradford
//C00223037
//Joint Assignment 2 
#include "BallotPaper.h"

void BallotPaper::setPreference(int preference, Candidate candidate)
{
	_candidates[preference] = candidate;
}
Candidate BallotPaper::getPreference(int preference)
{
	return _candidates[preference];
}