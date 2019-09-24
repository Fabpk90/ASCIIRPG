#pragma once

#include "Tile.h"

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Actor : public Tile
{

protected:
	Tile **tiles;
	int x;
	int y;
	int health;
	int damage;
	Direction dir;

public:
	Actor(int x, int y, int health, int damage, char character, DWORD colorMask, Tile **tiles);
	~Actor();

	virtual void Die() = 0;
	virtual void Update() = 0;

	virtual void TakeDamage(int amount);

	void SetTiles(Tile **tiles);
};

