#include "Enemy.h"

#include "Constants.h"
#include "GameManager.h"


Enemy::Enemy(int x, int y, int health, int damage, char c, WORD colorMask, std::vector<Tile*>& tiles)
	: Actor(x, y, health, damage, c, colorMask, tiles, TileType::ENEMY)
{}


Enemy::~Enemy()
{
}

bool Enemy::isObstacle()
{
	return true;
}

void Enemy::Die()
{
	tiles[y * SCREEN_HEIGHT + x] = GameManager::instance.ground;
}

void Enemy::Update()
{
	//TODO: AI !
}
