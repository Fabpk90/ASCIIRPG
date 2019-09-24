#include "Actor.h"

#include "Constants.h"

Actor::Actor(int x, int y, int health, int damage, char character, DWORD colorMask, std::vector<Tile*>& tiles, TileType type) : Tile(character, colorMask, type)
, health(health), damage(damage), x(x), y(y), tiles(tiles)
{
	this->tiles = tiles;
}

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
