#include "GameManager.h"

#include <iostream>

GameManager GameManager::instance = GameManager();


GameManager::GameManager()
{
	handleOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	handleInput = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);

	isGameRunning = true;

	m = nullptr;
}


GameManager::~GameManager()
{
}

void GameManager::LoadMap(const char * path)
{
	m = new Map(path);
}
