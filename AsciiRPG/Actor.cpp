#include "Actor.h"

#include "Constants.h"

Actor::Actor(int x, int y, int health, int damage, char character, DWORD colorMask, Tile **tiles) : Tile(character, colorMask)
, health(health), damage(damage), x(x), y(y)
{
	this->tiles = tiles;

	(*tiles)[y * SCREEN_HEIGHT + x].character = character;
	(*tiles)[y * SCREEN_HEIGHT + x].colorMask = colorMask;
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

void Actor::SetTiles(Tile ** tiles)
{
	this->tiles = tiles;

	(*tiles)[y * SCREEN_HEIGHT + x].character = character;
	(*tiles)[y * SCREEN_HEIGHT + x].colorMask = colorMask;
}
