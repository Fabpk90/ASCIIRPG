#pragma once

#include <Windows.h>
#include "Player.h"

class HUD
{
private:
	Player& player;
	
	//Size of the first dimension of the buffer
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

