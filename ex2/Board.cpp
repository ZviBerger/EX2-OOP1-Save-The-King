#include "Board.h"
#include<iostream>
#include<Windows.h>
#include <fstream>


Board::Board(std::string streamText)
{   //make connection with the text file and read it
	std::ifstream stream(streamText);  
	std::string oneLine;

	while (getline(stream, oneLine)) 
	{
		m_board.push_back(oneLine);
	}
	setEdge();
}
//==========================================================
bool Board::updateObjects(const Place &plc, const std::string& symbul)
{	
	if (!isInsideBoundaries(plc))
		return false;
			
	m_board[plc.m_x][plc.m_y] = symbul[0];  //to avoid convert      
	return true;	
}
//===========================================================
std::string Board::getOneChar(const Place &plc) const
{
	if( isInsideBoundaries(plc)  )
		return{ m_board[plc.m_x][plc.m_y] }	;

	return "!";
}

//=============================================================
void Board::printBoard() const
{	
		for (const auto& line : m_board)
		std::cout << line << "\n";
}
//=============================================================
void Board::clearBoard() const
{
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
}
//===============================================================
Place Board::getCharPlace(const std::string & c) const
{
	for ( int i = 0; i < m_board.size(); i++)
		for ( int j = 0; j < m_board[i].size(); j++)
			if (m_board[i][j] == c[0])
				return{ i,j };

	return{ 0,0 };
}
//===============================================================
Place Board::getEdge() const
{
	return m_edge;
}
std::vector<std::string> Board::getBoard() const
{
	return m_board;
}
//===============================================================
bool Board::isInsideBoundaries(const Place &plc) const
{
	return plc.m_x >= 0 && plc.m_y >= 0 && plc.m_x < m_edge.m_x && plc.m_y < m_edge.m_y;
}
//===============================================================
void Board::setEdge()
{   //update the "bottom-right" of the board:
	m_edge.m_x = m_board.size();
	m_edge.m_y = m_board[m_board.size() - 1].length();
}
