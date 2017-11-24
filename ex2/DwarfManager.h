#pragma once
#include "Dwarf.h"


class DwarfManager
{
public:
	DwarfManager(const Board &board);
	~DwarfManager();
	void updadeDwarfMoves(Board &board);  //updating position, checking if the Giant came one of them place by parameter, 
private:
	struct TargetDwarf
	{
		Dwarf _dwarf;
		bool _hasATarget;
		Place _target;
		std::string _targetSymbol;
		std::vector<Place> m_wayQueue;
	};

	struct Steps
	{
		int stepsCount;
		Place point;
		int back;

	};

	std::vector<TargetDwarf> m_dwarfsVector;
	std::vector<Steps> BFSArray;
	std::vector<std::string> tmp_board;
	std::vector<Place> m_bestTargets;
	int m_toSendByTarget = 2;
	Place m_edge;
	bool thiefHasAKey;
	void initDwarfsVector(const Board &board);
	
	void deliverTargates(const Board &board);
	void setEdge();
	bool updateObjects(const Place &plc, const std::string& symbul);
	std::string getOneChar(const Place &plc) const;
	bool isInsideBoundaries(const Place &plc) const;
	bool isClosser(const Place& place1, const Place & place2, const Place & target);
	void decideWhichTarget(const Board& board);

	void AddArray(const Place& point, const Place & target, int wc, int back);
	void findWay0(TargetDwarf & start, const Place& target,const Board& brd);
	bool isValidMove(const std::string &movementChar) const;
	void setTheTargets(const Board& board, const std::string & targetChar);
	void setTargetToDwarf(TargetDwarf & dwarf, const Board & board);

	};

