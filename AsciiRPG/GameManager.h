#pragma once

#include <Windows.h>
#include "Constants.h"
#include "InputHandler.h"
#include "Map.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	HANDLE handleOutput;
	HANDLE handleInput;

	InputHandler input;

	Map* m;
	Tile *ground;

	bool isGameRunning;

	static GameManager instance;

	void LoadMap(const char *path);
};
