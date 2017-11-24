#pragma once
#include<string>
#include "Board.h"

class King
{
public:
	King();
	King::King(const Place& firstPlace);
	King(int, int);
	bool go2(const Place& move, Board& brd);
	Place getPlace() const;
	bool gameOn() const;
private:
	Place m_kingPlace;
	bool m_onKey = false;
	bool m_gameOn = true;
	bool isValidMove(const std::string &movementChar) const;
    void King::updatePlace(const Place& move);
	
};

