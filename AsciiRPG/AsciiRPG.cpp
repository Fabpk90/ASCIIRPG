// AsciiRPG.cpp : définit le point d'entrée pour l'application console.
//

#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <iostream>
#include <windows.h>

#include "Constants.h"
#include "Map.h"
#include "GameManager.h"
#include "Dungeon.h"

int main()
{
	
	Map m("map.txt");
	Dungeon d(1);
	/*int i = 0;
	/*while (i < 1)
	{*/
		m.Draw();
		m.player->HandleInput();
		d.GenAlea();

		getchar();
	//}
	

    return 0;
}

