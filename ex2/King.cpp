#include "King.h"



King::King()
{}

King::King(int x, int y)
	:m_kingPlace{ x,y }  //first place on board
{}

King::King(const Place& firstPlace)
	: m_kingPlace{ firstPlace.m_x, firstPlace.m_y }  //first place on board
{}

//=============================================================================

bool King::go2(const Place& move, Board& brd)
{
	//copy next move place char
	std::string theMove = brd.getOneChar({ m_kingPlace.m_x + move.m_x, m_kingPlace.m_y + move.m_y });
	
	if (theMove == "@"){
		m_gameOn = false;
		return true;
	}
	if (isValidMove(theMove)){
		if (m_onKey){
			brd.updateObjects(m_kingPlace, "F");
			m_onKey = false;
		}
		else{
			brd.updateObjects(m_kingPlace, " ");
		}
		if (theMove == "F"){
			m_onKey = true;
		}
		

		updatePlace(move);
		brd.updateObjects(m_kingPlace, "K");
		return true;
	}
	return false;
}

//=============================================================================

Place King::getPlace() const
{
	return m_kingPlace;
}
bool King::gameOn() const
{
	return m_gameOn;
}
//============================================================================
bool King::isValidMove(const std::string & movementChar) const
{
	return movementChar == " " ||  movementChar == "F" ;
}

//=============================================================================

void King::updatePlace(const Place& move)
{
	m_kingPlace.m_x += move.m_x;
	m_kingPlace.m_y += move.m_y;
}


