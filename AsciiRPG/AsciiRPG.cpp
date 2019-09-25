// AsciiRPG.cpp : définit le point d'entrée pour l'application console.
//

#include "GameManager.h"

int main()
{
	GameManager& gm = GameManager::GetInstance();
	gm.LoadMap("map.txt");

	while (gm.isGameRunning)
	{
		gm.m->Draw();
	}

    return 0;
}

