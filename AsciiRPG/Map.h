#pragma once

#include "Constants.h"
#include <string>
#include <windows.h>
#include "Player.h"

struct Tile
{
	char character;
	WORD mask;
};

class Map
{

private:
	CHAR_INFO* buffer;
	Tile* tiles;

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	Player* player;
public:
	Map(const char* path);
	~Map();

	void Draw();

	WORD GetTileMaskValue(int val);
};

