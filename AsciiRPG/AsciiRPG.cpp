// AsciiRPG.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "GameManager.h"
#include "NYTimer.h"

int main()
{
	GameManager& gm = GameManager::GetInstance();
	gm.LoadMap("map.txt");

	NYTimer timer;
	timer.start();

	while (gm.isGameRunning)
	{
		if (timer.getElapsedMs() > TICK_TIME)
		{
			timer.start();
			gm.m->Draw();
		}
		
	}

    return 0;
}

