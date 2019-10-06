#include "Projectile.h"

#include "GameManager.h"




Projectile::Projectile(int x, int y, int damage, char character, Direction dir, std::vector<Tile*>& tiles, TileType shooterTileType)
	: Entity(x, y, dir, tiles, character, FOREGROUND_RED | FOREGROUND_GREEN, TileType::PROJECTILE), shooterTileType(shooterTileType), damage(damage)
{
	CheckTileForCollision(x, y);
}

Projectile::~Projectile()
{
}

void Projectile::Die()
{
	isActive = false;
	tiles[y * SCREEN_HEIGHT + x] = GameManager::GetInstance().groundTile;
	GameManager::GetInstance().m->EntityDies(this);
}

void Projectile::Update()
{
	CheckForCollision();
}

void Projectile::CheckForCollision()
{
	std::pair<int, int> position = GetPositionFromDirection();

	//if we can't move, we're hitting something
	PositionBlocked blockType = ChangePosition(position.first, position.second);

	if (blockType == OBSTACLE)
	{
		CheckTileForCollision(position.first, position.second);
	}
	else if (blockType == OUT_OF_BOUND)
		Die();
}

void Projectile::CheckTileForCollision(int x, int y)
{
	TileType type = tiles[y * SCREEN_HEIGHT + x]->type;

	if (type == TILE)
		Die();
	else if (type == ENEMY || type == PLAYER)
	{
		if (type != shooterTileType)
		{
			Actor* a = static_cast<Actor*>(tiles[y * SCREEN_HEIGHT + x]);
			a->TakeDamage(damage);

			Die();
		}
		else //we don't hurt our creator
			Die();
	}
}
