#pragma once
#include "King.h"
#include "Giant.h"
#include "Mage.h"	
#include "Thief.h"
#include "Board.h"
#include "Dwarf.h"
#include "Input.h"
#include "DwarfManager.h"
class Controller
{
public:
	Controller();
	//interface functions:
	void runGames(std::string levelsPathFile);
private:
	struct m_players
	{
		King  _king;
		Giant _giant;
		Mage  _mage;
		Thief _thif;
	};
	std::vector <std::string > m_gameLevel;           //contain links to all game levels files
	std::vector <std::string > m_startingScreens;
	int m_levelNum=0;
	int m_score=0;
	Input m_input;
	bool runLevel(const unsigned int  & Mylevel);
	void uploadLevels(std::string levelsPathFile);
	void Controller::clearAndPrint(const Board &board) const;
	bool isDirection(const KEYS &command) const;
	void printStatus(const int &movements, const bool &hasAKay, const std::string  & player)const;
	bool executeCommand(const KEYS& command, struct m_players& players, int &playerNum,Board &board);
	void runStartingScreens();
	void printPage(const std::string &pageName) const;
};

