#pragma once
#include<string>
#include "Structures.h"
#include "Board.h"

class Thief
{
public:
	Thief();
	Thief(int, int);
	Thief(const Place& firstPlace);
	bool go2(const Place& move, Board& brd);
	Place getPlace() const;
	bool hasAKay() const;
private:
	Place m_thiefPlace;
	bool m_onKey = false;
	bool m_hasKey = false;
	bool isValidMove(const std::string &movementChar) const;
	void Thief::updatePlace(const Place& move);
};

