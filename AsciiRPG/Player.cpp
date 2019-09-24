#include "Player.h"

#include "GameManager.h"
#include "Enemy.h"
#include <iostream>

Player::Player(int health, int damage, char c) : Actor(health, damage, c, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
{
	dir = Direction::DOWN;
	x = 2;
	y = 3;
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
				if(inputBuffer[i].Event.KeyEvent.bKeyDown)
				switch (inputBuffer[i].Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_LEFT:
					if (x - 1 >= 0)
						if (ChangePosition(x - 1, y))
							dir = LEFT;
							
					break;
				case VK_RIGHT:
					if (x + 1 < SCREEN_WIDTH)
						if (ChangePosition(x + 1, y))
							dir = RIGHT;
					break;

				case VK_UP:
					if (y - 1 >= 0)
						if (ChangePosition(x, y - 1))
							dir = UP;
					break;
				case VK_DOWN:
					if (y + 1 < SCREEN_HEIGHT)
						if (ChangePosition(x, y + 1))
							dir = DOWN;
					break;

				case VK_ESCAPE:
					GameManager::instance.isGameRunning = false;
					break;
				}
			}
		}

		delete inputBuffer;
	}
}

bool Player::ChangePosition(int x, int y)
{
	//TODO: check collisions

	if (!((*tiles)[y * SCREEN_HEIGHT + x]).isObstacle())
	{
		(*tiles)[this->y * SCREEN_HEIGHT + this->x].character = ' ';
		(*tiles)[this->y * SCREEN_HEIGHT + this->x].colorMask = 0;

		(*tiles)[y * SCREEN_HEIGHT + x].character = character;
		(*tiles)[y * SCREEN_HEIGHT + x].colorMask = colorMask;

		this->y = y;
		this->x = x;

		return true;
	}

	return false;
}

bool Player::AttackAt(int x, int y)
{
	if (!((*tiles)[y * SCREEN_HEIGHT + x]).isObstacle())
	{
		if (Enemy* enemy = dynamic_cast<Enemy*>((&((*tiles))[y * SCREEN_HEIGHT + x])))
		{

		}

		return true;
	}

	return false;
}

void Player::Die()
{
	GameManager::instance.isGameRunning = false;
}
