#include "GameManager.h"

#include <iostream>

GameManager GameManager::instance = GameManager();


GameManager::GameManager()
{
	std::cout << "yay";
	handle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
}


GameManager::~GameManager()
{
}
