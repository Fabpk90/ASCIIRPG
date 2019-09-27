// AsciiRPG.cpp : définit le point d'entrée pour l'application console.
//

#include <io.h>
#include <fcntl.h>

#include "GameManager.h"
#include "NYTimer.h"


int main()
{
	GameManager& gm = GameManager::GetInstance();
	gm.LoadMap("map.txt");

	NYTimer* timer = new NYTimer();
	timer->start();

	while (gm.isGameRunning)
	{
		if (timer->getElapsedMs() > TICK_TIME)
		{
			timer->start();
			gm.m->Draw();
		}
	}

	delete timer;
	
    return 0;
}

