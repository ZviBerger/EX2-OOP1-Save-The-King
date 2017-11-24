#pragma once
#include<string>
#include "Structures.h"
#include "Board.h"

class Giant
{
public:
	Giant();
	Giant(int , int );
	Giant(const Place& firstPlace);

	bool go2(const Place& move, Board& brd);
	Place getPlace() const;

private:
	Place m_giantPlace;
	bool m_onKey = false;
	bool isValidMove(const std::string &movementChar) const;
	void Giant::updatePlace(const Place& move);

};

