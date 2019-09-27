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

public:

	~GameManager();

	HANDLE handleOutput;
	HANDLE handleInput;

	Map* m;
	Tile *ground;

	bool isGameRunning;

	static GameManager& GetInstance();

	void LoadMap(const char *path);
	void Win();

	DWORD getInput(INPUT_RECORD **eventBuffer);
};
