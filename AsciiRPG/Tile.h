#pragma once

#include <Windows.h>

enum TileType
{
	ENV = 0,
	TILE,
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

	bool isObstacle();
};

