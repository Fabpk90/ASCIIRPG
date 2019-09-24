#pragma once

#include "Constants.h"
#include <string>
#include <windows.h>
#include "Player.h"
#include "Enemy.h"
#include <vector>


class Map
{

private:
	CHAR_INFO* buffer;
	
	Player* player;
	Enemy* enemy;

	std::vector<Actor*> actors;

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	std::vector<Tile*> tiles;

	void UpdateBuffer();

public:
	Map(const char* path);
	~Map();

	void Draw();

	WORD GetTileMaskValue(int val);

	//Assumes that the size doesn't change
	void LoadMap(const char *path);
};

