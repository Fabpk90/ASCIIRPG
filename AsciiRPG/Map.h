#pragma once

#include "Constants.h"
#include <string>
#include <windows.h>
#include "Player.h"

class Map
{

private:
	HANDLE hOutput;

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	Player* player;
public:
	Map(const char* path);
	~Map();

	void Draw();

	WORD GetTileMaskValue(int val);
};

