#include "Enemy.h"

#include "Constants.h"
#include "GameManager.h"
#include "Projectile.h"

#include <iostream>


Enemy::Enemy(int x, int y, Direction dir, int health, int damage, char c, WORD colorMask, std::vector<Tile*>& tiles)
	: Actor(x, y, dir, health, damage, c, colorMask, tiles, TileType::ENEMY)
{
	framePassed = 0;
	dir = DOWN;

	weapon = new Weapon(*this, 1.5f);
}


Enemy::~Enemy()
{
	delete weapon;
}

void Enemy::Die()
{
	isActive = false;
	tiles[y * SCREEN_HEIGHT + x] = GameManager::GetInstance().groundTile;
	GameManager::GetInstance().m->EntityDies(this);
}

void Enemy::Update()
{
	//HAX
	tiles[y * SCREEN_HEIGHT + x] = this;
	//HAX

	if ((++framePassed % frameBeforeTick) == 0)
	{
		FollowTarget();
		framePassed = 0;
	}
}

PositionBlocked Enemy::ChangePosition(int x, int y)
{
	if (tiles[y * SCREEN_HEIGHT + x]->type != EXIT)
	{
		return Entity::ChangePosition(x, y);
	}

	return OBSTACLE;
}

void Enemy::FollowTarget()
{
	Actor& actor = GameManager::GetInstance().m->GetPlayer();

	//trying to reach the player
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

	//diagonal movemment are not allowed
	if (moveX != x && moveY != y)
		moveY = y;
	
	if (tiles[moveY * SCREEN_HEIGHT + moveX]->type == TileType::PLAYER)
	{
		Actor* a = static_cast<Actor*>(tiles[moveY * SCREEN_HEIGHT + moveX]);
		a->TakeDamage(damage);
	}
	else //we can't hit the player, so we try to move
	{
		PositionBlocked blockType = ChangePosition(moveX, moveY);

		if (blockType == OBSTACLE)
		{
			Tile* t = tiles[moveY * SCREEN_HEIGHT + moveX];

			//maybe we hit a projectile
			if (t->type == PROJECTILE)
			{
				Projectile* p = static_cast<Projectile*>(t);

				//last check, to see if the projectile is still active
				if (p->GetIsActive())
				{
					TakeDamage(p->GetDamage());
					p->Die();
				}
				
				ChangePosition(moveX, moveY);
			}
		}
		else //maybe we can shoot at the player
		{
			weapon->Use();
		}
	}
}
