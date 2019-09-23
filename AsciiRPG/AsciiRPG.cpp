// AsciiRPG.cpp : définit le point d'entrée pour l'application console.
//

#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <iostream>
#include <windows.h>

#include "Constants.h"
#include "Map.h"

int main()
{
	Map m("map.txt");
	m.Draw();

	getchar();

    return 0;
}

