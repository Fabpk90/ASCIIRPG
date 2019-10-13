#pragma once

#include <Windows.h>
#include "Constants.h"
#include "Map.h"

#include "NYTimer.h"

class GameManager
{
private:
	GameManager();
	
	static GameManager *instance;
	int level;
	int maxLevel;

public:

	~GameManager();

	HANDLE handleOutput;
	HANDLE handleInput;

	Map* m;
	Tile *groundTile;
	Tile *wallTile;
	Tile* exitTile;

	bool isGameRunning;

	int GetLevel() { return level; }

	static GameManager& GetInstance();

	void LoadMap(const char *path);
	void Win();
	void NextLevel();

	DWORD getInput(INPUT_RECORD **eventBuffer);
};
