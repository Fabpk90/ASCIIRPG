#pragma once

#include <Windows.h>
#include "Constants.h"
#include "InputHandler.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	HANDLE handleOutput;
	HANDLE handleInput;

	InputHandler input;

	static GameManager instance;
};
