// AsciiRPG.cpp�: d�finit le point d'entr�e pour l'application console.
//

#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <iostream>
#include <windows.h>

#include "Constants.h"
#include "Map.h"

int main()
{
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	buffer[5][10].Char.AsciiChar = 'H';
	buffer[5][10].Attributes = FOREGROUND_RED | FOREGROUND_GREEN;
	buffer[5][11].Char.AsciiChar = 'i';
	buffer[5][11].Attributes = 9;
	buffer[5][12].Char.AsciiChar = '!';
	buffer[5][12].Attributes = 10;

	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	Map m("map.txt");
	m.Draw();

	getchar();

    return 0;
}

