//Christian Bradford
//C00223037
//Joint Assignment 2 
#include "Candidate.h"

Candidate::Candidate(std::string name, std::string party)
{
	_name = name;
	_party = party;
}
std::string const Candidate::GetName()
{
	return _name;
}
std::string Candidate::GetParty()
{
	return _party;
}
void Candidate::SetName(std::string name)
{
	_name = name;
}
void Candidate::SetParty(std::string party)
{
	_party = party;
}
bool Candidate::operator == (Candidate &d)
{
	return _name == d.GetName();
}
bool Candidate::operator != (Candidate &d)
{
	return _name != d.GetName();
}