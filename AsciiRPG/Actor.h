#pragma once

#include "Tile.h"
#include <vector>

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
	std::vector<Tile*>& tiles;
	int x;
	int y;
	int health;
	int damage;
	Direction dir;

public:
	Actor(int x, int y, int health, int damage, char character, DWORD colorMask, std::vector<Tile*>& tiles, TileType type);
	~Actor();

	int GetX() { return x; }
	int GetY() { return y; }

	virtual void Die() = 0;
	virtual void Update() = 0;

	virtual void TakeDamage(int amount);

	void SetTiles(std::vector<Tile*>& tiles);
};

