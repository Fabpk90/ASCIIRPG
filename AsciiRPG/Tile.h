#pragma once

#include <Windows.h>
#include <winnt.h>

enum TileType
{
	ENV = 0,
	TILE,
	ENEMY,
	PLAYER,
	PROJECTILE,
	DOOR,
	EXIT
};


//Represents the minimal object in the game
class Tile
{
public:
	Tile();
	Tile(wchar_t character, WORD colorMask, TileType type);
	virtual ~Tile();

	wchar_t character;
	WORD colorMask;
	TileType type;

	bool isObstacle() const;
};

