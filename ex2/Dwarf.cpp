#include "Dwarf.h"
#include <stdlib.h>
#include <time.h>
#include<iostream>

using std::cout;


Dwarf::Dwarf()
{
}

Dwarf::Dwarf(int x, int y)
	:m_startDwarfPl{ x,y }, m_runDwarfPlace{ x,y }
{
	
}

Dwarf::Dwarf(const Place & place)
	: m_startDwarfPl{ place.m_x,place.m_y }, m_runDwarfPlace{ place.m_x,place.m_y }
{
}


//===========================================================
//gets a target and board and does the next step
bool Dwarf::go2(const Place& target, Board & brd)
{ 
	Place newPlace;
	if (target != Place{ 0,0 } && 
		(std::abs(m_runDwarfPlace.m_x - target.m_x) + std::abs(m_runDwarfPlace.m_y - target.m_y) == 1)&&
		isValidMove(brd.getOneChar(target)))
	{
	//	std::cout << "not rando" << std::endl;
		newPlace = target;
	}
	else
	{
		//std::cout << "rando" << std::endl;
		newPlace = randSide(m_runDwarfPlace, brd);//gets random move
	}
	//
	//if ((m_wayQueue.empty() && target != Place{ 1000,1000 }) || (!m_wayQueue.empty() && target != m_lastTarget))         //if is a target
	//{
	//	findWay0(m_runDwarfPlace, target, brd);//findes the shortest way to it
	//	m_lastTarget = target;
	//}
	//if (!m_wayQueue.empty() && target != m_wayQueue.back() && isValidMove(brd.getOneChar(m_wayQueue.back())))
	//{
	//	newPlace = m_wayQueue.back();
	//	m_wayQueue.pop_back();
	//}
	//else
	//{
	//	std::cout << "rando" << std::endl;
	//	newPlace = randSide(m_runDwarfPlace, brd);//gets random move
	//}
	if (newPlace != m_runDwarfPlace)//if place changed
	{
		if (m_onKey)//if was a key on the place
		{
			brd.updateObjects(m_runDwarfPlace, "F");
			m_onKey = false;
		}
		else
		{
			brd.updateObjects(m_runDwarfPlace, " ");
		}
		if (brd.getOneChar(newPlace) == "F")//if the's a key on new place 
		{
			m_onKey = true;
		}
	}
	updatePlace(newPlace);
	brd.updateObjects(m_runDwarfPlace, "^");
	return true;
}

//===========================================================
//returns the place of dwarf
Place Dwarf::getPlace() const
{
	return m_runDwarfPlace;
}

//===========================================================

void Dwarf::setDFirstPlace( Board& brd)
{
	if (isValidMove(brd.getOneChar(m_startDwarfPl)))
	{
		m_runDwarfPlace = m_startDwarfPl;
		brd.updateObjects(m_runDwarfPlace, "^");
	}
}

//===========================================================

bool Dwarf::isValidMove(const std::string & movementChar) const
{
	return (movementChar == " " || movementChar == "F");
}

//===========================================================
//sets new place
void Dwarf::updatePlace(const Place & move)
{
	m_runDwarfPlace.m_x = move.m_x;
	m_runDwarfPlace.m_y = move.m_y;
}

//===========================================================
//returns random movement 
Place Dwarf::randSide(const Place & start, Board & brd)
{
	unsigned side;
	Place newPlace;
	srand(time(NULL));

	if (sidesOpen(start, brd))
	{
		//gets random movement 
		do
		{
			side = rand() % 4;
			if (side == 0)
			{
				newPlace = start + movement(RIGHT);
			}
			else if (side == 1)
			{
				newPlace = start + movement(DOWN);
			}
			else if (side == 2)
			{
				newPlace = start + movement(LEFT);
			}
			else
			{
				newPlace = start + movement(UP);
			}
		} while (!isValidMove(brd.getOneChar(newPlace)));
	}
	else
	{
		newPlace = start;
	}
	return newPlace;
}
//===========================================================
//returns true if unlees one way is open
bool Dwarf::sidesOpen(const Place & start, Board & brd) const
{
	return (isValidMove(brd.getOneChar(start + movement(RIGHT))) ||
		isValidMove(brd.getOneChar(start + movement(DOWN))) ||
		isValidMove(brd.getOneChar(start + movement(LEFT))) ||
		isValidMove(brd.getOneChar(start + movement(UP))));
}

//===========================================================
/*
void Dwarf::setEdge()
{
	m_edge.m_x = tmp_board.size();
	m_edge.m_y = tmp_board[tmp_board.size() - 1].length();
}

//===========================================================

bool Dwarf::updateObjects(const Place & plc, const std::string & symbul)
{
	if (!isInsideBoundaries(plc))
		return false;

	tmp_board[plc.m_x][plc.m_y] = symbul[0];  //to avoid convert      
	return true;
}

//===========================================================

std::string Dwarf::getOneChar(const Place & plc) const
{
	if (isInsideBoundaries(plc))
		return{ tmp_board[plc.m_x][plc.m_y] };
	return "!";
}

//===========================================================

bool Dwarf::isInsideBoundaries(const Place & plc) const
{
	return plc.m_x >= 0 && plc.m_y >= 0 && plc.m_x < m_edge.m_x && plc.m_y < m_edge.m_y;
}

//===========================================================

void Dwarf::AddArray(const Place & point,  const Place & target, int wc, int back)
{
	if(isValidMove(getOneChar(point)) || (point == target))
	{
		updateObjects(point, "$");
		Steps tmp;
		tmp.point = point;
		tmp.stepsCount = wc;
		tmp.back = back;
		BFSArray.push_back( tmp );
	}
	//else if (point == target)
	//{
	//	Steps tmp;
	//	tmp.point = point;
	//	tmp.stepsCount = wc;
	//	tmp.back = back;
	//	BFSArray.push_back(tmp);	
	//}
}

//===========================================================

void Dwarf::findWay0(const Place & start, const Place & target,
	Board & brd)
{
	tmp_board = brd.getBoard();
	setEdge();

	BFSArray.clear();
	Steps tmp;
	tmp.point = start;
	tmp.stepsCount = 0;
	tmp.back = -1;
	BFSArray.push_back(tmp);

	int i = 0;
	while (i < BFSArray.size()) 
	{
		if (BFSArray[i].point == target)
		{
			m_wayQueue.clear();
			Place tmp2;
			while (BFSArray[i].stepsCount != 0)
			{
				tmp2 = BFSArray[i].point;
				m_wayQueue.push_back(tmp2);
				i = BFSArray[i].back;
			}
			break;
		}
		AddArray(BFSArray[i].point + movement(RIGHT), target, BFSArray[i].stepsCount + 1, i);
		AddArray(BFSArray[i].point + movement(DOWN), target, BFSArray[i].stepsCount + 1, i);
		AddArray(BFSArray[i].point + movement(LEFT), target, BFSArray[i].stepsCount + 1, i);
		AddArray(BFSArray[i].point + movement(UP), target, BFSArray[i].stepsCount + 1, i);
		
		i++;
	}
	BFSArray.clear();
}
*/
/*
//===========================================================
//findes next step
Place Dwarf::findWay1(const Place & start, const Place & target, Board & brd)
{

int rightLength, leftLength, downLength, upLength;
Place right = start + movement(RIGHT);
Place down = start + movement(DOWN);
Place left = start + movement(LEFT);
Place up = start + movement(UP);
if (isValidMove(brd.getOneChar(right)))
{
if (target == right)
return right;
rightLength = findWay2(right, start, target, 0, brd);
}
else
{
rightLength = 1000;
}
if (isValidMove(brd.getOneChar(down)))
{
if (target == down)
return down;
downLength = findWay2(down, start, target, 0, brd);
}
else
{
downLength = 1000;
}
if (isValidMove(brd.getOneChar(left)))
{
if (target == left)
return left;
leftLength = findWay2(left, start, target, 0, brd);
}
else
{
leftLength = 1000;
}
if (isValidMove(brd.getOneChar(up)))
{
if (target == up)
return up;
upLength = findWay2(up, start, target, 0, brd);
}
else
{
upLength = 1000;
}
if (rightLength <= min(downLength, min(leftLength, upLength)))
{
return right;
}
else if (downLength <= min(rightLength, min(leftLength, upLength)))
{
return down;
}
else if (leftLength <= min(downLength, min(rightLength, upLength)))
{
return left;
}
else if (upLength <= min(downLength, min(leftLength, rightLength)))
{
return up;
}
else
{
return randSide(m_runDwarfPlace, brd);
}
}
//===========================================================
//returns the length of shortest way to target
int Dwarf::findWay2(const Place & start, const Place & last, const Place & target, int steps, Board & brd)
{
//cout << "Way2: " << counterWay2 << std::endl;
//counterWay2++;

Place right = start + movement(RIGHT);
Place down = start + movement(DOWN);
Place left = start + movement(LEFT);
Place up = start + movement(UP);
int step[3] = { 1000 }, i = 0;


if (start == target)
return 0;
if (steps >= 10)
return 1000;
if (right != last && right != m_runDwarfPlace)
{
if (isValidMove(brd.getOneChar(right)) || right == target)
{

step[i] = 1 + findWay2(right, start, target, steps + 1, brd);
//cout << "right" << i << std::endl;
}
i++;
}
if (down != last && down != m_runDwarfPlace)
{
if (isValidMove(brd.getOneChar(down)) || down == target)
{
step[i] = 1 + findWay2(down, start, target, steps + 1, brd);
//cout << "down" << i << std::endl;

}
i++;
}
if (left != last && left != m_runDwarfPlace)
{
if (isValidMove(brd.getOneChar(left)) || left == target)
{

step[i] = 1 + findWay2(left, start, target, steps + 1, brd);
//cout << "left" << i << std::endl;
}
i++;
}
if (up != last && up != m_runDwarfPlace)
{
if (isValidMove(brd.getOneChar(up)) || up == target)
{

step[i] = 1 + findWay2(up, start, target, steps + 1, brd);
//cout << "up" << i << std::endl;
}
i++;
}
//cout << min(step[0], min(step[1], step[2])) << std::endl;
return (min(step[0], min(step[1], step[2])));
}

//===========================================================
//returns true if valid movement
int Dwarf::min(int x, int y)
{
	return x > y ? y : x;
}

void Dwarf::printBoard() const
{
for (const auto& line : tmp_board)
std::cout << line << "\n";
}
*/