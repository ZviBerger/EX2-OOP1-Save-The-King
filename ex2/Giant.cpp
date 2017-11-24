#include "Giant.h"



Giant::Giant(){}

Giant::Giant(int x, int y)
	:m_giantPlace{ x,y }  //first place on board
{}

Giant::Giant(const Place & firstPlace)
	: m_giantPlace{ firstPlace.m_x,firstPlace.m_y }
{
}

//=============================================================================

bool Giant::go2(const Place & move, Board & brd)
{
	std::string theMove = brd.getOneChar({ m_giantPlace.m_x + move.m_x, m_giantPlace.m_y + move.m_y });
	if (isValidMove(theMove))
	{
		if (m_onKey)
		{
			brd.updateObjects(m_giantPlace, "F");
			m_onKey = false;
		}
		else
		{
			brd.updateObjects(m_giantPlace, " ");
		}
		if (theMove == "F")
		{
			m_onKey = true;
		}
		
		updatePlace(move);
		brd.updateObjects(m_giantPlace, "G");
		return true;
	}
	return false;
}

//=============================================================================

Place Giant::getPlace() const
{
	return m_giantPlace;
}

//=============================================================================

bool Giant::isValidMove(const std::string & movementChar) const
{
	return (movementChar == " " || movementChar == "^" || movementChar == "F");
}

//=============================================================================

void Giant::updatePlace(const Place & move)
{
	m_giantPlace.m_x += move.m_x;
	m_giantPlace.m_y += move.m_y;
}
