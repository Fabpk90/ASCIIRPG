#include "Player.h"

#include "GameManager.h"
#include <iostream>

Player::Player(char c, Tile** tiles) 
{
	characterOnMap = c;
	x = 2;
	y = 3;
	this->tiles = tiles;
}


Player::~Player()
{
}

void Player::HandleInput()
{
	INPUT_RECORD* inputBuffer = nullptr;
	DWORD numEventRead = GameManager::instance.input.getInput(&inputBuffer);

	if (numEventRead)
	{
		for (int i = 0; i < numEventRead; i++)
		{
			switch (inputBuffer[i].EventType)
			{
			case KEY_EVENT:
				switch (inputBuffer[i].Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_LEFT:
					if (x - 1 >= 0)
						ChangePosition(x - 1, y);
					break;
				case VK_RIGHT:
					if (x + 1 < SCREEN_WIDTH)
						ChangePosition(x + 1, y);
					break;

				case VK_UP:
					if (y - 1 >= 0)
						ChangePosition(x, y - 1);
					break;
				case VK_DOWN:
					if (y + 1 < SCREEN_HEIGHT)
						ChangePosition(x, y + 1);
					break;
				}
			}
		}

		delete inputBuffer;
	}

	

}

void Player::ChangePosition(int x, int y)
{
	//TODO: check collisions

	if ((*tiles)[y * SCREEN_HEIGHT + x].character == ' ')
	{
		(*tiles)[this->y * SCREEN_HEIGHT + this->x].character = ' ';
		(*tiles)[this->y * SCREEN_HEIGHT + this->x].mask = 0;

		(*tiles)[y * SCREEN_HEIGHT + x].character = characterOnMap;
		(*tiles)[y * SCREEN_HEIGHT + x].mask = color;

		this->y = y;
		this->x = x;
	}
}
