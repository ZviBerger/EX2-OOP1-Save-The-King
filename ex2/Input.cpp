#include "Input.h"
#include <cstdlib>      // for system()
#include <conio.h>      // for _kbhit() and _getch()
#include<string>
Input::Input()
{
}

KEYS Input::getNextKey() const
{
	
	int kayCode = 0;
	do
	{
    // Wait for a key to be pressed
    while (!_kbhit())      
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	kayCode = _getch();
	switch (kayCode)
	{
	case 0:
	case SPECIAL_KEY:
		return getSpecialKey();
	case KB_ESCAPE:
		return ESCAPE;
	case KB_P:
		return CHANGE;
	case KB_SPACE:
		return SPACE;
	default:
		return UNKNOWN;
		break;
	}
		
	} while (kayCode != KB_ESCAPE);

}
//========================================================
KEYS Input::getSpecialKey() const
{
	KEYS key;
	int c = _getch();
	switch (c)
	{
	case KB_ESCAPE:
		key= ESCAPE;
		break;

	case KB_UP:
		key = UP;
		break;

	case KB_DOWN:
		key = DOWN;
		break;

	case KB_LEFT:
		key = LEFT;
		break;

	case KB_RIGHT:
		key = RIGHT;
		break;

	default:
		key = UNKNOWN;
		break;

	}

	return key;
}
//===============================================
