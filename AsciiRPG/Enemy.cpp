#include "Enemy.h"



Enemy::Enemy(int health, int damage) : health(health), damage(damage)
{}


Enemy::~Enemy()
{
}

bool Enemy::isObstacle()
{
	return true;
}
