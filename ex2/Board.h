#pragma once
#include <vector>
#include <string>
#include "Structures.h"

class Board
{
public:
	Board(std::string  streamText); //constructor
	bool updateObjects(const Place &plc,const std::string& symbul);
	std::string getOneChar(const Place &plc) const;
	void printBoard() const;
	void clearBoard() const;
	Place getCharPlace(const std::string& c) const;
	Place getEdge() const;
	std::vector<std::string> getBoard()const;

private:
	std::vector<std::string> m_board;
	Place m_edge;
	bool isInsideBoundaries(const Place &plc) const;
	void setEdge();
	
};

