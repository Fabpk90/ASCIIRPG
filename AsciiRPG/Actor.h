#pragma once

#include "Tile.h"
#include "Entity.h"
#include <vector>

class Actor : public Entity
{

protected:
	int health;
	int damage;
	

public:
	Actor(int x, int y, Direction dir, int health, int damage, char character, WORD colorMask, std::vector<Tile*>& tiles, TileType type);
	~Actor();

	virtual void TakeDamage(int amount);

	
	bool AttackAt(int x, int y);

	virtual void Die() = 0;
	virtual void Update() = 0;

	void SetTiles(std::vector<Tile*>& tiles);
};

