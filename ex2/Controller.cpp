#include "Controller.h"
#include <fstream>


Controller::Controller()
{
}
//=================================================================================
void Controller::runGames(std::string levelsPathFile)
{ 
	runStartingScreens();

	//read all screens and level activate one by one
	uploadLevels(levelsPathFile);

	//for any level call runLevel function
	for (unsigned int level = 0; level < m_gameLevel.size(); level++)
	{
		runLevel(level);
		printPage("endLevel.txt");
	}
}
//=================================================================================
void Controller::uploadLevels(std::string  levelsPathFile)
{
	std::ifstream stream(levelsPathFile) ;
	std::string level;
	while (getline(stream, level))
	{
		m_gameLevel.push_back(level);
	}
}
//=================================================================================
bool Controller::runLevel(const unsigned int  & Mylevel)
{
	if (Mylevel >= m_gameLevel.size())
		return false;
	//initialize the current board level
	Board board(m_gameLevel[Mylevel]);  
	
	
	//level variables 
	m_players players;
	players._king = board.getCharPlace("K");
	players._giant = board.getCharPlace("G");
	players._mage = board.getCharPlace("M");
	players._thif = board.getCharPlace("T");
	
	DwarfManager dWmanager{ board };
	

	KEYS  nextCommand;   //next command in ENUM value
	bool moved = false;  
	int playerNum = 0, movementCounter = 0;
	std::string playerNow[4]{ "KING","MAGE","THIF", "GIANT" };
	
	board.printBoard();
	printStatus(movementCounter, players._thif.hasAKay(), playerNow[playerNum]);

	//the core of the game:
	do {	
		nextCommand = m_input.getNextKey();
		moved = executeCommand(nextCommand, players, playerNum, board);
		if (moved || nextCommand== SPACE)
		{
			dWmanager.updadeDwarfMoves(board);
			clearAndPrint(board); 
			movementCounter++;
			printStatus(movementCounter, players._thif.hasAKay(), playerNow[playerNum]);
		}
		
	} while (players._king.gameOn());

	return  true;
}

//=================================================================================
void Controller::clearAndPrint(const Board &board) const
{   
	board.clearBoard();
	board.printBoard();
}
//=================================================================================

bool Controller::isDirection(const KEYS & command) const
{
	return command == UP || command == DOWN || command == RIGHT || command == LEFT;
}
//=================================================================================

void Controller::printStatus(const int & movements, const bool & hasAKey,const std::string  & player)const
{

	std::cout << "Number Of Movements: " << movements << std::endl;
	std::cout << "The Thief ";
	if (hasAKey)
		std::cout << "Has A Key!!!\n";
	else 
		std::cout << "Has NO Key!\n";

	std::cout << "The player is the: " << player << std::endl;
	
}

//=================================================================================
bool Controller::executeCommand(const KEYS & command, m_players & players, int & playerNum,Board &board)
{
	bool moved = false;
	Place nextPlace;

	switch (command) {
	case UP: case DOWN: case RIGHT: case LEFT:
		nextPlace = movement(command);  //in case of movement 
		switch (playerNum) {
		case 0:
			moved = players._king.go2(nextPlace, board);
			break;
		case 1:
			moved = players._mage.go2(nextPlace, board);
			break;
		case 2:
			moved = players._thif.go2(nextPlace, board);
			break;
		case 3:
			moved = players._giant.go2(nextPlace, board);
			break;
		default:
			break;
		}
		break;

	case ESCAPE:
		return true;
	case CHANGE:
		playerNum = (playerNum + 1) % 4;
		break;
	default:
		break;
	}

	return moved;
}
//=================================================================================

void Controller::runStartingScreens()
{
	std::ifstream stream("StartingScreens.txt");

	std::string pages;
	while (getline(stream, pages))
		printPage(pages);
}
//================================================================================
void Controller::printPage(const std::string & pageName) const
{
	Board newPage(pageName);
	newPage.printBoard();
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	std::system("cls");

}
//=================================================================================