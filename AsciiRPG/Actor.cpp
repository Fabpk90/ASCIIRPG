#include "Actor.h"

#include "Constants.h"
#include "GameManager.h"

Actor::Actor(int x, int y, Direction dir, int health, int damage, char character, WORD colorMask, std::vector<Tile*>& tiles, TileType type) 
	: Entity(x, y, dir, tiles, character, colorMask, type)
, health(health), damage(damage)
{}

Actor::~Actor()
{
}

void Actor::TakeDamage(int amount)
{
	if (health - amount <= 0)
	{
		Die();
	}
	else
	{
		health -= amount;
	}
}

void Actor::SetTiles(std::vector<Tile*>& tiles)
{
	this->tiles = tiles;

	tiles[y * SCREEN_HEIGHT + x]->character = character;
	tiles[y * SCREEN_HEIGHT + x]->colorMask = colorMask;
}

bool Actor::AttackAt(int x, int y)
{
	Tile *tile = tiles[y * SCREEN_HEIGHT + x];

	if (tile->type == ENEMY)
	{
		Actor* a = static_cast<Actor*>(tiles[y * SCREEN_HEIGHT + x]);
		a->TakeDamage(damage);

		return true;
	}

	return false;
}
