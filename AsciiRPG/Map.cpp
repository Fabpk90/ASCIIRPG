#include "Map.h"

#include <iostream>
#include <fstream>

Map::Map(const char * path)
{
	std::ifstream stream(path);

	if (!stream.fail())
	{
		std::string str;
		char c;
		int att = 0;
		int width = 0;
		while (std::getline(stream ,str))
		{
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] != ' ')
				{
					std::cout << str[i++];
					std::cout << str[i];
				}
				else
					std::cout << ' ';
			}

			std::cout << std::endl;
			width++;
		}
		stream.close();
	}
	
}

Map::~Map()
{
}

void Map::Draw()
{
}

WORD Map::GetTileMaskValue(int val)
{
	//TODO: check la val

	WORD d;

	switch (val)
	{
	case 1:
		d |= FOREGROUND_RED;
		break;
	case 2:
		d |= FOREGROUND_BLUE;
		break;

	case 3:
		d |= FOREGROUND_GREEN;
		break;

	case 4:
		d |= FOREGROUND_GREEN | FOREGROUND_RED;
		break;

	case 5:
		d |= FOREGROUND_BLUE | FOREGROUND_GREEN;
		break;

	case 6:
		d |= FOREGROUND_RED | FOREGROUND_BLUE;
		break;

	case 7: 
		d |= FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		break;

	default:
		break;
	}

	return d;
}
