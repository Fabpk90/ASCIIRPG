#pragma once

#include "Tile.h"

class Enemy : public Tile
{
private:
	int health;
	int damage;
public:
	Enemy(int health, int damage);
	~Enemy();

	bool isObstacle() override;
};

