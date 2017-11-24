#pragma once
#include "Board.h"
#include <vector>
class Dwarf
{
public:
	Dwarf();
	Dwarf(int, int);
	Dwarf(const Place& place);
	bool go2(const Place& target, Board& brd);
	Place getPlace() const;
	void setDFirstPlace(Board& brd);

	struct Steps
	{
		int stepsCount;
		Place point;
		int back;

	};

private:

	std::vector<Place> m_wayQueue;
	std::vector<Steps> BFSArray;
	Place m_startDwarfPl;
	Place m_runDwarfPlace;
	bool m_onKey = false;
	Place m_edge;
	Place m_lastTarget;
	std::vector<std::string> tmp_board;


	void setEdge();
	bool updateObjects(const Place &plc, const std::string& symbul);
	std::string getOneChar(const Place &plc) const;
	bool isInsideBoundaries(const Place &plc) const;

	void AddArray(const Place& point, const Place & target, int wc, int back);
	void findWay0(const Place& start, const Place& target, Board& brd);
	bool isValidMove(const std::string &movementChar) const;
	void Dwarf::updatePlace(const Place& move);
	Place randSide(const Place& start, Board & brd);
	bool sidesOpen(const Place& start, Board & brd)const;

	//int min(int, int);
	//Place findWay1(const Place& start, const Place& target, Board& brd);
	//int findWay2(const Place& start, const Place & last, const Place& target, int steps, Board& brd);
};

