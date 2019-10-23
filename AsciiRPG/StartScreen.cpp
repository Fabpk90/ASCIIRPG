#include "StartScreen.h"
#include "GameManager.h"


StartScreen::StartScreen(short posX, short posY)
{
	text = "Press enter to start the game";
	
	dwBufferSize.X = text.size();
	dwBufferSize.Y = 1;

	dwBufferCoord.X = dwBufferCoord.Y = 0;

	buffer = new CHAR_INFO[text.size() + 1];
	
	rcRegion = { posX, posY, SCREEN_HEIGHT + (SHORT)text.size(), SCREEN_WIDTH };
	
	ReadConsoleOutput(GameManager::GetInstance().handleOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	for (size_t i = 0; i < text.size(); i++)
	{
		buffer[i].Char.AsciiChar = text[i];
	}
}

void StartScreen::Draw()
{
	WriteConsoleOutput(GameManager::GetInstance().handleOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void StartScreen::Clear()
{
	for (size_t i = 0; i < text.size(); i++)
	{
		buffer[i].Char.AsciiChar = ' ';
	}

	WriteConsoleOutput(GameManager::GetInstance().handleOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}


StartScreen::~StartScreen()
{	
	delete[] buffer;
}
