#pragma once

#include <Windows.h>
#include "Player.h"

class HUD
{
private:
	Player& player;
	short sizeX;

	CHAR_INFO* buffer;

	COORD dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT rcRegion;

	std::string healthText;

public:
	HUD(short sizeX, short posX, short posY, Player& player);
	~HUD();
	void Draw();
};

