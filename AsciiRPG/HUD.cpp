#include "HUD.h"

#include "GameManager.h"


HUD::HUD(short sizeX, short posX, short posY, Player & player) :
	sizeX(sizeX), posX(posX), posY(posY), player(player)
{
	dwBufferSize.X = sizeX;
	dwBufferSize.Y = 1;

	dwBufferCoord.X = dwBufferCoord.Y = 0;

	rcRegion = { posX, posY, SCREEN_HEIGHT + posX, SCREEN_WIDTH};

	healthText = "health: ";
	healthBaseSize = 8;

	buffer = new CHAR_INFO[sizeX + healthBaseSize];
	

	ReadConsoleOutput(GameManager::GetInstance().handleOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	for (size_t i = 0; i < sizeX; i++)
	{
		buffer[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}

	for (size_t i = 0; i < healthBaseSize; i++)
	{
		buffer[i].Char.AsciiChar = healthText[i];
	}

}

HUD::~HUD()
{
	delete[] buffer;
}

void HUD::Draw()
{
	int health = player.GetHealth();
	std::string str = std::to_string(health);

	for (int i = 0; i < str.length(); i++)
	{
		buffer[i + healthBaseSize].Char.AsciiChar = str[i];
	}

	WriteConsoleOutput(GameManager::GetInstance().handleOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}
