#pragma once
#include <Windows.h>
#include <string>

class StartScreen
{
private:
	CHAR_INFO* buffer;

	COORD dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT rcRegion;

	std::string text;
public:
	StartScreen(short posX, short posY);
	void Draw();
	void Clear();
	~StartScreen();
};

