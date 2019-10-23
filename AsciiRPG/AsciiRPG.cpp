// AsciiRPG.cpp : définit le point d'entrée pour l'application console.
//

#include <io.h>

#include "GameManager.h"
#include "NYTimer.h"
#include "StartScreen.h"


int main()
{
	GameManager& gm = GameManager::GetInstance();
	gm.LoadMap("map.txt");

	NYTimer* timer = new NYTimer();
	timer->start();

	StartScreen start(5, 5);
	INPUT_RECORD* input = nullptr;

	bool keyPressed = false;
	
	//ugly menu
	/*do
	{
		start.Draw();
		gm.getInput(&input);

		if (input && input->Event.KeyEvent.bKeyDown)
			keyPressed = true;
	} while (!keyPressed);*/

	start.Draw();
	getchar();
	start.Clear();

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