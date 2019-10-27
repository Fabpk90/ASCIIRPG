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

	//current level
	int level;

	//indicates the number of level to generate
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

	int GetLevel() const { return level; }

	static GameManager& GetInstance();

	void LoadMap(const char *path);
	void Win();
	void NextLevel();

	DWORD getInput(INPUT_RECORD **eventBuffer);
};
