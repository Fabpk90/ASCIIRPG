#pragma once

#include "Constants.h"
#include <string>
#include <windows.h>

struct Tile
{
	char c;
	WORD attr;
};

class Map
{

private:
	Tile tiles[SCREEN_WIDTH][SCREEN_HEIGHT];
public:
	Map(const char* path);
	~Map();

	void Draw();

	WORD GetTileMaskValue(int val);
};

