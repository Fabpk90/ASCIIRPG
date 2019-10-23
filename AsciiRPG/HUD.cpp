#include "HUD.h"

#include "GameManager.h"


HUD::HUD(short sizeX, short posX, short posY, Player & player) :
	sizeX(sizeX), player(player)
{
	dwBufferSize.X = sizeX;
	dwBufferSize.Y = 1;

	dwBufferCoord.X = dwBufferCoord.Y = 0;

	rcRegion = { posX, posY, SCREEN_HEIGHT + posX, SCREEN_WIDTH};

	healthText = "health: ";
	

	buffer = new CHAR_INFO[sizeX + healthText.size()];
	

	ReadConsoleOutput(GameManager::GetInstance().handleOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	for (size_t i = 0; i < sizeX; i++)
	{
		buffer[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}

	for (size_t i = 0; i < healthText.size(); i++)
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
		buffer[i + healthText.size()].Char.AsciiChar = str[i];
	}

	WriteConsoleOutput(GameManager::GetInstance().handleOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}
