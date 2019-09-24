#include "Enemy.h"

#include "Constants.h"


Enemy::Enemy(int x, int y, int health, int damage, char c, WORD colorMask, Tile **tiles) 
	: Actor(x, y, health, damage, c, colorMask, tiles)
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
	(*tiles)[y * SCREEN_HEIGHT + x].character = ' ';
	(*tiles)[y * SCREEN_HEIGHT + x].colorMask = 0;
}

void Enemy::Update()
{
	//TODO: AI !
}
