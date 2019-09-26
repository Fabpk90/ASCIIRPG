#include "Player.h"

#include "GameManager.h"
#include "Enemy.h"
#include "Projectile.h"
#include <iostream>

Player::Player(int x, int y, Direction dir, int health, int damage, char c, std::vector<Tile*>& tiles, TileType type)
	: Actor(x, y, dir, health, damage, c, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, tiles, type)
{
	isUntouchable = false;
	untouchableFramePassed = 0;

	colorNormal = colorMask;
	colorHit = FOREGROUND_RED;
}


Player::~Player()
{
}

void Player::HandleInput()
{
	INPUT_RECORD* inputBuffer = nullptr;
	DWORD numEventRead = GameManager::GetInstance().getInput(&inputBuffer);

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
					{
						ChangePosition(x - 1, y);
						dir = LEFT;
					}
							
					break;
				case VK_RIGHT:
					if (x + 1 < SCREEN_WIDTH)
					{
						dir = RIGHT;
						ChangePosition(x + 1, y);
					}
					break;

				case VK_UP:
					if (y - 1 >= 0)
					{
						ChangePosition(x, y - 1);
						dir = UP;
					}
					break;
				case VK_DOWN:
					if (y + 1 < SCREEN_HEIGHT)
					{
						ChangePosition(x, y + 1);
						dir = DOWN;
					}
					break;

				case VK_ESCAPE:
					GameManager::GetInstance().isGameRunning = false;
					break;
					
				case VK_RETURN:
					{
						std::pair<int, int> pos = GetPositionFromDirection();
						AttackAt(pos.first, pos.second);
					}
					break;

				case VK_CONTROL:
					Shoot();
					break;
				}
			}
		}

		delete inputBuffer;
	}
}

void Player::Die()
{
	isActive = false;
	GameManager::GetInstance().isGameRunning = false;
}

void Player::Update()
{
	if (isUntouchable)
	{
		if (++untouchableFramePassed % untouchableFrames == 0)
		{
			isUntouchable = false;
			colorMask = colorNormal;
		}
			
	}

	HandleInput();
}

void Player::TakeDamage(int damage)
{
	if (!isUntouchable)
	{
		Actor::TakeDamage(damage);
		isUntouchable = true;
		colorMask = colorHit;

		untouchableFramePassed = 0;
	}
}

void Player::Shoot()
{
	std::pair<int, int> position = GetPositionFromDirection();

	if (position.first > 0 && position.first < SCREEN_WIDTH
		&& position.second > 0 && position.second < SCREEN_HEIGHT)
	{
		//TODO: TEST !!!
		if (!tiles[position.first * SCREEN_HEIGHT + position.second]->isObstacle())
		{
			GameManager::GetInstance().m->AddEntity(new Projectile(position.first, position.second, 2, '*', dir, tiles, type));
		}
	}
}
