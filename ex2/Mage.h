#pragma once
#include<string>
#include "Structures.h"
#include "Board.h"

class Mage
{
public:
	Mage();
	Mage(int , int );
	Mage(const Place &firstPlace);
	bool go2(const Place& move, Board& brd);
	Place getPlace() const;

private:
	Place m_magePlace;
	bool m_onKey = false;
	bool isValidMove(const std::string &movementChar) const;
	void Mage::updatePlace(const Place& move);

};

