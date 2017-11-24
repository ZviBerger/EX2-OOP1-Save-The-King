#include "DwarfManager.h"
#include <cmath>
#include<iostream>

using std::cout;

DwarfManager::DwarfManager(const Board &board)
{
	initDwarfsVector(board);
	deliverTargates(board);
	decideWhichTarget(board);
}


DwarfManager::~DwarfManager()
{
}
//==========================================================

void DwarfManager::initDwarfsVector(const Board & board)
{
	m_edge = board.getEdge();
	for (int i = 0; i < m_edge.m_x; i++)
	{
		for (int j = 0; j <m_edge.m_y; j++)
		{
			std::string oneChar = board.getOneChar(Place{ i, j });
			if (oneChar[0] == '^')
			{
				TargetDwarf newDwarf;
				newDwarf._dwarf ={ i,j };
				newDwarf._hasATarget = false;
				newDwarf._target = { 0,0 };
				newDwarf._targetSymbol = " ";
				m_dwarfsVector.push_back(newDwarf);
			}
		}
	}
}
//================================================================
void DwarfManager::updadeDwarfMoves( Board &board)
{
	for (unsigned int i = 0; i < m_dwarfsVector.size(); i++)  //go over the vector
		if (board.getOneChar(m_dwarfsVector[i]._dwarf.getPlace()) == "^")
		{
			if (m_dwarfsVector[i]._hasATarget && m_dwarfsVector[i].m_wayQueue.empty() )
			{
//				std::cout << "updadeDwarfMoves1" << i <<std::endl;
				setTargetToDwarf(m_dwarfsVector[i], board);
			}
			if (m_dwarfsVector[i]._hasATarget && !m_dwarfsVector[i].m_wayQueue.empty())
			{
				//std::cout << "updadeDwarfMoves2" << i << std::endl;
				m_dwarfsVector[i]._dwarf.go2(m_dwarfsVector[i].m_wayQueue.back(), board);
				m_dwarfsVector[i].m_wayQueue.pop_back();
			}
			else
			{
				//std::cout << "updadeDwarfMoves3" << i << std::endl;
				m_dwarfsVector[i]._dwarf.go2(Place{ 0,0 }, board);
			}
		}
		else
		{
			m_dwarfsVector[i]._dwarf.setDFirstPlace(board);
		}
}

//===============================================================
void DwarfManager::deliverTargates(const Board & board)
{
	setTheTargets(board, "@");
	setTheTargets(board, "K");
	//setTheTargets(board, "*");
	setTheTargets(board, "T");
	setTheTargets(board, "M");
	setTheTargets(board, "F");

}
//===============================================================
void DwarfManager::setEdge()
{
	m_edge.m_x = tmp_board.size();
	m_edge.m_y = tmp_board[tmp_board.size() - 1].length();
}

//===============================================================

bool DwarfManager::updateObjects(const Place & plc, const std::string & symbul)
{
	if (!isInsideBoundaries(plc))
		return false;

	tmp_board[plc.m_x][plc.m_y] = symbul[0];  //to avoid convert      
	return true;
}

//===============================================================

std::string DwarfManager::getOneChar(const Place & plc) const
{
	if (isInsideBoundaries(plc))
		return{ tmp_board[plc.m_x][plc.m_y] };
	return "!";
}

//===============================================================

bool DwarfManager::isInsideBoundaries(const Place & plc) const
{
	return plc.m_x >= 0 && plc.m_y >= 0 && plc.m_x < m_edge.m_x && plc.m_y < m_edge.m_y;
}

//===============================================================

bool DwarfManager::isClosser(const Place & place1, const Place & place2, const Place & target)
{
	return ((std::abs(place1.m_x - target.m_x) + std::abs(place1.m_y - target.m_y)) >
		(std::abs(place2.m_x - target.m_x) + std::abs(place2.m_y - target.m_y)));
}

void DwarfManager::decideWhichTarget(const Board & board)
{
	int byTarget = 0;
	for (size_t i = 0; i < m_bestTargets.size() && byTarget < m_toSendByTarget; i++)
	{
		Place first = { 1000,1000 };
		TargetDwarf* tmpTD{ nullptr };
		for (size_t j = 0; j < m_dwarfsVector.size(); j++)
		{
			if(!m_dwarfsVector[j]._hasATarget)
				if (isClosser(first, m_dwarfsVector[j]._dwarf.getPlace(), m_bestTargets[i]))
				{	
					if (first != Place{ 1000,1000 })
					{
						tmpTD->_hasATarget = false;
						tmpTD->_target = Place{ 0,0 };
					}
					first = m_dwarfsVector[j]._dwarf.getPlace();
					tmpTD = &m_dwarfsVector[j];
					m_dwarfsVector[j]._hasATarget = true;
					m_dwarfsVector[j]._target = m_bestTargets[i];
				}
		}
		for (size_t i = 0; i < m_dwarfsVector.size(); i++)
		{
			if (m_dwarfsVector[i]._hasATarget)
			{
				findWay0(m_dwarfsVector[i], m_dwarfsVector[i]._target, board);
				if (m_dwarfsVector[i].m_wayQueue.empty())
				{
					m_dwarfsVector[i]._hasATarget = false;
					m_dwarfsVector[i]._target = Place{ 0,0 };
				}
				else
				{
					
					m_dwarfsVector[i]._targetSymbol = getOneChar(m_dwarfsVector[i]._dwarf.getPlace());
					byTarget++;
				}
			}
		}
	}
}

//===============================================================

void DwarfManager::AddArray(const Place & point, const Place & target, int wc, int back)
{
	if (isValidMove(getOneChar(point)) || (point == target))
	{
		updateObjects(point, "$");
		Steps tmp;
		tmp.point = point;
		tmp.stepsCount = wc;
		tmp.back = back;
		BFSArray.push_back(tmp);
	}
}

//===============================================================

void DwarfManager::findWay0(TargetDwarf & start, const Place & target,const Board & brd)
{
	
	tmp_board = brd.getBoard();
	setEdge();

	BFSArray.clear();
	Steps tmp;
	tmp.point = start._dwarf.getPlace();
	tmp.stepsCount = 0;
	tmp.back = -1;
	BFSArray.push_back(tmp);

	int i = 0;
	int bfsaSize = BFSArray.size();
	while (i < bfsaSize)
	{
		if (BFSArray[i].point == target)
		{
			start.m_wayQueue.clear();
			Place tmp2;
			while (BFSArray[i].stepsCount != 0)
			{
				tmp2 = BFSArray[i].point;
				start.m_wayQueue.push_back(tmp2);
				i = BFSArray[i].back;
			}
		//	std::cout << "findWay0" << std::endl;
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

//===============================================================

bool DwarfManager::isValidMove(const std::string & movementChar) const
{
	return (movementChar == " " || movementChar == "F");
}

//===============================================================

void DwarfManager::setTargetToDwarf(TargetDwarf & dwarf,const Board & board)
{
	
	std::vector<Place> tmpTargets;
	dwarf.m_wayQueue.clear();
	int i = 0;
	int bestTargetsSize = m_bestTargets.size();

	while (dwarf.m_wayQueue.empty() && i <bestTargetsSize)
	{
		findWay0(dwarf, m_bestTargets.back(), board);
		if (dwarf.m_wayQueue.empty())
		{
			Place temp = m_bestTargets.back();
			tmpTargets.push_back(temp);
			m_bestTargets.pop_back();
		}
		else
		{
			dwarf._target = m_bestTargets.back();
			m_bestTargets.pop_back();
			dwarf._targetSymbol = getOneChar(dwarf._target);
		}
		i++;
	}
	while (!tmpTargets.empty())
	{
		Place temp = tmpTargets.back();
		m_bestTargets.push_back(temp);
		tmpTargets.pop_back();
	}
	tmpTargets.clear();
}

//===============================================================

void DwarfManager::setTheTargets(const Board& board, const std::string & targetChar)
{
	for (int i = 0; i < m_edge.m_x; i++)
	{
		for (int j = 0; j < m_edge.m_y; j++)
		{
			std::string oneChar = board.getOneChar(Place{ i, j });
			if (oneChar[0] == targetChar[0])
			{
				Place newTarget = { i,j };
				m_bestTargets.push_back(newTarget);
			}
		}
	}
}
//===============================================================

