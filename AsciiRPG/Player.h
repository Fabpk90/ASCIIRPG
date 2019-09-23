#pragma once

#include <Windows.h>

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

public:
	Player(char c);
	~Player();

	int GetX() { return x; }
	int GetY() { return y; }

	char GetCharacter() { return characterOnMap; }
	WORD GetColor() { return color; }

	void HandleInput();
};

