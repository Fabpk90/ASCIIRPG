#include "Enemy.h"

#include "Constants.h"
#include "GameManager.h"

#include <iostream>


Enemy::Enemy(int x, int y, int health, int damage, char c, WORD colorMask, std::vector<Tile*>& tiles)
	: Actor(x, y, health, damage, c, colorMask, tiles, TileType::ENEMY)
{
	framePassed = 0;
}


Enemy::~Enemy()
{
}

bool Enemy::isObstacle()
{
	return true;
}

void Enemy::Die()
{
	tiles[y * SCREEN_HEIGHT + x] = GameManager::GetInstance().ground;
}

void Enemy::Update()
{
	//TODO: AI !

	if ((++framePassed % frameBeforeTick) == 0)
	{
		ChangePosition(x + 1, y);
		framePassed = 0;
	}

}
