#include "Thief.h"



Thief::Thief()
{
}

Thief::Thief(int x, int y)
	:m_thiefPlace{ x,y }  //first place on board
{
}

Thief::Thief(const Place & firstPlace)
	: m_thiefPlace{ firstPlace.m_x,firstPlace.m_y }
{
}

bool Thief::go2(const Place & move, Board & brd)
{

	std::string theMove = brd.getOneChar({ m_thiefPlace.m_x + move.m_x, m_thiefPlace.m_y + move.m_y });
	if (isValidMove(theMove))
	{
		if (m_onKey)
		{
			brd.updateObjects(m_thiefPlace, "F");
			m_onKey = false;
		}
		else
		{
			brd.updateObjects(m_thiefPlace, " ");
		}
		if (theMove == "F")
		{
			if (m_hasKey)
			{
				m_onKey = true;
			}
			else
			{
				m_hasKey = true;
			}
		}
		else if (theMove == "#")
		{
			m_hasKey = false;
		}
		updatePlace(move);
		brd.updateObjects(m_thiefPlace, "T");
		return true;
	}
	return false;
}

Place Thief::getPlace() const
{
	return m_thiefPlace;
}

bool Thief::hasAKay() const
{
	return m_hasKey;
}

bool Thief::isValidMove(const std::string & movementChar) const
{
	return (movementChar == " " ||  movementChar == "F" ||(m_hasKey && movementChar == "#"));
}

void Thief::updatePlace(const Place & move)
{
	m_thiefPlace.m_x += move.m_x;
	m_thiefPlace.m_y += move.m_y;
}

