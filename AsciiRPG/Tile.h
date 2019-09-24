#pragma once

#include <Windows.h>


class Tile
{
public:
	Tile();
	Tile(char character, WORD colorMask);
	~Tile();

	char character;
	WORD colorMask;

	virtual bool isObstacle();
};

