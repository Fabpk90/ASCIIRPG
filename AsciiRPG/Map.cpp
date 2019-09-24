#include "Map.h"

#include <iostream>
#include <fstream>


#include "GameManager.h"

Map::Map(const char * path)
{
	buffer = new CHAR_INFO[SCREEN_HEIGHT * SCREEN_WIDTH];
	tiles = new Tile[SCREEN_HEIGHT * SCREEN_WIDTH];

	

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			tiles[i * SCREEN_HEIGHT + j].character = ' ';
			tiles[i * SCREEN_HEIGHT + j].colorMask = 0;
		}
	}

	//sert � init le buffer
	ReadConsoleOutput(GameManager::instance.handleOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	LoadMap(path);
	player = new Player(3, 2, 10, 2, '@', &tiles);
	enemy = new Enemy(3, 3, 5, 2, '!', FOREGROUND_BLUE | FOREGROUND_GREEN, &tiles);

	actors.push_back(player);
	actors.push_back(enemy);
}

Map::~Map()
{
	delete player;
	delete[] buffer;
	delete[] tiles;
}

void Map::Draw()
{
	for (Actor* a : actors)
	{
		a->Update();
	}

	UpdateBuffer();


	WriteConsoleOutput(GameManager::instance.handleOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Map::UpdateBuffer()
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			buffer[i * SCREEN_HEIGHT + j].Char.AsciiChar = tiles[i * SCREEN_HEIGHT + j].character;
			buffer[i * SCREEN_HEIGHT + j].Attributes = tiles[i * SCREEN_HEIGHT + j].colorMask;
		}
	}
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

void Map::LoadMap(const char * path)
{
	std::ifstream stream(path);

	if (!stream.fail())
	{
		for (Actor* a : actors)
		{
			//TODO: find a better solution
			if (auto p = dynamic_cast<Player*>(a))
			{

			}
			else
			{
				delete a;
			}
		}

		actors.clear();

		for (int i = 0; i < SCREEN_HEIGHT; i++)
		{
			for (int j = 0; j < SCREEN_WIDTH; j++)
			{
				tiles[i * SCREEN_HEIGHT + j].character = ' ';
				tiles[i * SCREEN_HEIGHT + j].colorMask = 0;
			}
		}

		std::string str;
		char c;
		int att = 0;
		int width = 0;
		int height = 0;
		while (std::getline(stream, str))
		{
			width = 0;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] != ' ')
				{
					buffer[height * SCREEN_HEIGHT + width].Char.AsciiChar = str[i];
					buffer[height * SCREEN_HEIGHT + width].Attributes = GetTileMaskValue((int)(str[i + 1] - '0'));

					tiles[height * SCREEN_HEIGHT + width].character = str[i];
					tiles[height * SCREEN_HEIGHT + width].colorMask = buffer[height * SCREEN_HEIGHT + width].Attributes;

					i++;
				}

				width++;
			}
			height++;
		}
		stream.close();
	}
}
