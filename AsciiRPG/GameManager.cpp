#include "GameManager.h"

#include <iostream>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	handleOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	handleInput = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);

	isGameRunning = true;
	level = 0;
	maxLevel = 3;

	m = nullptr;
	groundTile = new Tile(' ', 0, ENV);
	wallTile = new Tile('X', FOREGROUND_GREEN, TILE);
	exitTile = new Tile('E', FOREGROUND_GREEN | FOREGROUND_RED, EXIT);
}


GameManager::~GameManager()
{
	delete instance;
	delete m;
	delete groundTile;
	delete wallTile;
	delete exitTile;
}

GameManager & GameManager::GetInstance()
{
	if (!instance)
	{
		instance = new GameManager();
	}

	return *instance;
}

void GameManager::LoadMap(const char * path)
{
	m = new Map(path);
}

void GameManager::Win()
{
	//TODO: add a better ending
	isGameRunning = false;
}

void GameManager::NextLevel()
{
	if (++level == maxLevel)
		Win();
	else
		m->LoadMap();
}

DWORD GameManager::getInput(INPUT_RECORD ** eventBuffer)
{
	/* Variable for holding the number of current events, and a point to it */
	DWORD numEvents = 0;


	/* Variable for holding how many events were read */
	DWORD numEventsRead = 0;


	/* Put the number of console input events into numEvents */
	GetNumberOfConsoleInputEvents(GameManager::GetInstance().handleInput, &numEvents);


	if (numEvents) /* if there's an event */
	{
		/* Allocate the correct amount of memory to store the events */
		*eventBuffer = new INPUT_RECORD[numEvents];

		/* Place the stored events into the eventBuffer pointer */
		ReadConsoleInput(GameManager::GetInstance().handleInput, *eventBuffer, numEvents, &numEventsRead);
	}


	/* Return the amount of events successfully read */
	return numEventsRead;
}
