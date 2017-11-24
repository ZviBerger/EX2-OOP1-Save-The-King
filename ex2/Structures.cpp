#include "Structures.h"
//------------------------------------------
Place movement(const enum KEYS& side)
{
	Place move2;
	switch (side)
	{
	case UP:
		move2 ={ -1,0 };
		break;
	case RIGHT:
		move2 ={ 0,1 };
		break;
	case DOWN:
		move2 ={ 1,0 };
		break;
	case LEFT:
		move2 ={ 0,-1 };
		break;
	default:
		move2 = { 0,0 };
		break;
	}
	return move2;

}
//-----------------------------------------
bool Place::operator == (const Place & other) const {
	return (this->m_x == other.m_x && this->m_y == other.m_y);
}
//-----------------------------------------
Place  Place::operator + (const Place & other) const
{
	return{ this->m_x + other.m_x ,this->m_y + other.m_y };
}
//-------------------------------------------
bool Place::operator != (const Place & other) const {
	return !(*this == other);
}