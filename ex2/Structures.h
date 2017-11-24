#pragma once
#include<string>
//---------------------------------------
enum KEYS { UP, RIGHT, DOWN, LEFT, ESCAPE, CHANGE, SPACE, UNKNOWN };
//----------------------------------------
struct Place
{   int m_x;
	int m_y;
	bool Place::operator== (const Place & other) const; 
	Place  Place::operator+ (const Place & other) const;
	bool Place::operator!= (const Place & other) const;
};
//------------------------------------------
Place movement(const enum KEYS& side);

