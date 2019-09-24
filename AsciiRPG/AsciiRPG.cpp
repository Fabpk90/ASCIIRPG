// AsciiRPG.cpp : définit le point d'entrée pour l'application console.
//


#include "stdafx.h"
#include <iostream>
#include <windows.h>

#include "Constants.h"
#include "Map.h"
#include "GameManager.h"

#include "Player.h"

int main()
{
	GameManager::instance.LoadMap("map.txt");

	while (GameManager::instance.isGameRunning)
	{
		GameManager::instance.m->Draw();
	}

    return 0;
}

