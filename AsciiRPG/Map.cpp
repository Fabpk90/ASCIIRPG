#include "Map.h"

#include <iostream>
#include <fstream>

Map::Map(const char * path)
{
	player = new Player('@');

	hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	std::ifstream stream(path);

	if (!stream.fail())
	{
		std::string str;
		char c;
		int att = 0;
		int width = 0;
		int height = 0;
		while (std::getline(stream ,str))
		{
			width = 0;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] != ' ')
				{
					buffer[height][width].Char.AsciiChar = str[i];
					buffer[height][width].Attributes = GetTileMaskValue((int)(str[i+1] - '0'));
					i++;
				}

				width++;
			}
			height++;
		}
		stream.close();
	}

	buffer[player->GetY()][player->GetX()].Char.AsciiChar = player->GetCharacter();
	buffer[player->GetY()][player->GetX()].Attributes = player->GetColor();
	
}

Map::~Map()
{
	delete player;
}

void Map::Draw()
{

	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

WORD Map::GetTileMaskValue(int val)
{
	//TODO: check la val

	WORD d;

	switch (val)
	{
	case 1:
		d = FOREGROUND_RED;
		break;
	case 2:
		d = FOREGROUND_BLUE;
		break;

	case 3:
		d = FOREGROUND_GREEN;
		break;

	case 4:
		d = FOREGROUND_GREEN | FOREGROUND_RED;
		break;

	case 5:
		d = FOREGROUND_BLUE | FOREGROUND_GREEN;
		break;

	case 6:
		d = FOREGROUND_RED | FOREGROUND_BLUE;
		break;

	case 7: 
		d = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		break;

	default:
		break;
	}

	return d;
}
