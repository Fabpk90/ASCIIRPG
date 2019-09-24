#pragma once

#include <Windows.h>

enum TileType
{
	ENV = 0,
	ENEMY,
	PLAYER
};

class Tile
{
public:
	Tile();
	Tile(char character, WORD colorMask, TileType type);
	~Tile();

	char character;
	WORD colorMask;
	TileType type;

	virtual bool isObstacle();
};

