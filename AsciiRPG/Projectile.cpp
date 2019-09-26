#include "Projectile.h"

#include "GameManager.h"




Projectile::Projectile(int x, int y, int damage, char character, Direction dir, std::vector<Tile*>& tiles, TileType shooterTileType)
	: Entity(x, y, dir, tiles, character, FOREGROUND_RED, TileType::ENV), shooterTileType(shooterTileType), damage(damage)
{
	framePassed = 0;
}

Projectile::~Projectile()
{
}

void Projectile::Die()
{
	GameManager::GetInstance().m->EntityDies(this);
}

void Projectile::Update()
{
	if ((++framePassed % tickPerSecond) == 0)
	{
		framePassed = 0;
		CheckForCollision();
	}
}

void Projectile::CheckForCollision()
{
	std::pair<int, int> position = GetPositionFromDirection();

	//if we can't move, we're hitting something
	PositionBlocked blockType = ChangePosition(position.first, position.second);

	if (blockType == OBSTACLE)
	{
		TileType type = tiles[position.second * SCREEN_HEIGHT + position.first]->type;

		if (type == TILE)
			Die();
		else if (type == ENEMY || type == PLAYER)
		{
			if (type != shooterTileType)
			{
				Actor* a = static_cast<Actor*>(tiles[position.second * SCREEN_HEIGHT + position.first]);
				a->TakeDamage(damage);
				Die();
			}
			else //we don't hurt our creator
				Die();
		}
	}
	else if (blockType == OUT_OF_BOUND)
		Die();
}
