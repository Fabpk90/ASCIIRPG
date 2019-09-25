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

void Enemy::Die()
{
	tiles[y * SCREEN_HEIGHT + x] = GameManager::GetInstance().ground;
	GameManager::GetInstance().m->ActorDies(this);
}

void Enemy::Update()
{
	//TODO: AI !

	if ((++framePassed % frameBeforeTick) == 0)
	{
		FollowTarget();
		framePassed = 0;
	}

}

void Enemy::FollowTarget()
{
	Actor& actor = GameManager::GetInstance().m->GetPlayer();

	int targetX = actor.GetX();
	int targetY = actor.GetY();

	int moveX = x;
	int moveY = y;

	if (targetX > x)
		moveX += 1;
	else if (targetX < x)
		moveX -= 1;

	if (targetY > y)
		moveY += 1;
	else if (targetY < y)
		moveY -= 1;

	
	if (tiles[moveY * SCREEN_HEIGHT + moveX]->type == TileType::PLAYER)
	{
		Actor* a = static_cast<Actor*>(tiles[moveY * SCREEN_HEIGHT + moveX]);
		a->TakeDamage(damage);
	}

	ChangePosition(moveX, moveY);
}
