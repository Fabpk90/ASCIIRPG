#pragma once

#include <Windows.h>
#include "Constants.h"
#include "Tile.h"

enum Direction
{

};

class Player
{
private:
	int x;
	int y;

	Direction dir;

	char characterOnMap;
	WORD color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

	Tile** tiles;

public:
	Player(char c, Tile** tiles);
	~Player();

	int GetX() { return x; }
	int GetY() { return y; }

	char GetCharacter() { return characterOnMap; }
	WORD GetColor() { return color; }

	void HandleInput();
	void ChangePosition(int x, int y);
};

