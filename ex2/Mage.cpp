#include "Mage.h"



Mage::Mage()
{
}

Mage::Mage(int x, int y)
	:m_magePlace{ x,y }  //first place on board
{
}

Mage::Mage(const Place & firstPlace)
	:m_magePlace{firstPlace.m_x,firstPlace.m_y}
{
}

//=============================================================================

bool Mage::go2(const Place & move, Board & brd)
{
	std::string theMove = brd.getOneChar({ m_magePlace.m_x + move.m_x, m_magePlace.m_y + move.m_y });
	if (isValidMove(theMove))
	{
		if (m_onKey)
		{
			brd.updateObjects(m_magePlace, "F");
			m_onKey = false;
		}
		else
		{
			brd.updateObjects(m_magePlace, " ");
		}
		if (theMove == "F")
		{
			m_onKey = true;
		}
	
		updatePlace(move);
		brd.updateObjects(m_magePlace, "M");
		return true;
	}
	return false;
}

//=============================================================================

Place Mage::getPlace() const
{
	return m_magePlace;
}

//=============================================================================

bool Mage::isValidMove(const std::string &movementChar) const
{
	return (movementChar == " " || movementChar == "*" || movementChar == "F");
}

//=============================================================================

void Mage::updatePlace(const Place & move)
{
	m_magePlace.m_x += move.m_x;
	m_magePlace.m_y += move.m_y;
}
