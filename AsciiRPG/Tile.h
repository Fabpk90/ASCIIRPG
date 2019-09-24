#pragma once

#include <Windows.h>


class Tile
{

public:
	Tile();
	~Tile();

	char character;
	WORD mask;
};

