#include "GameManager.h"

#include <iostream>

GameManager GameManager::instance = GameManager();


GameManager::GameManager()
{
	handleOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	handleInput = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);
}


GameManager::~GameManager()
{
}
