// AsciiRPG.cpp�: d�finit le point d'entr�e pour l'application console.
//

#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <iostream>
#include <windows.h>

#include "Constants.h"
#include "Map.h"
#include "GameManager.h"

int main()
{
	
	Map m("map.txt");
	while (true)
	{

	}
	m.Draw();

    return 0;
}

