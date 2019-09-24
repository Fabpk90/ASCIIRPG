#include "Player.h"

#include "GameManager.h"
#include "Enemy.h"
#include <iostream>

Player::Player(int x, int y, int health, int damage, char c, std::vector<Tile*>& tiles, TileType type)
	: Actor(x, y, health, damage, c, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, tiles, type)
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
					GameManager::instance.isGameRunning = false;
					break;
					
				case VK_RETURN:
					std::pair<int, int> pos = GetPositionFromDirection();
					AttackAt(pos.first, pos.second);
				}
			}
		}

		delete inputBuffer;
	}
}

std::pair<int, int> Player::GetPositionFromDirection()
{
	std::pair<int, int> position;
	switch (dir)
	{
	case UP:
		position.first = x;
		position.second = y - 1;
		break;

	case RIGHT:
		position.first = x + 1;
		position.second = y;
		break;

	case DOWN:
		position.first = x;
		position.second = y + 1;
		break;

	case LEFT:
		position.first = x - 1;
		position.second = y;
		break;
	default:
		break;
	}

	return position;
}

bool Player::ChangePosition(int x, int y)
{
	//TODO: check collisions

	if (!(tiles[y * SCREEN_HEIGHT + x])->isObstacle())
	{
		tiles[this->y * SCREEN_HEIGHT + this->x] = GameManager::instance.ground;

		tiles[y * SCREEN_HEIGHT + x] = this;

		this->y = y;
		this->x = x;

		return true;
	}

	return false;
}

bool Player::AttackAt(int x, int y)
{
	Tile *tile = tiles[y * SCREEN_HEIGHT + x];

	if (tile->type == ENEMY)
	{
		Enemy* e = static_cast<Enemy*>(tiles[y * SCREEN_HEIGHT + x]);
		e->TakeDamage(damage);

		return true;
	}

	return false;
}

void Player::Die()
{
	GameManager::instance.isGameRunning = false;
}

void Player::Update()
{
	HandleInput();
}
