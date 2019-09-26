#pragma once

#include "Entity.h"

const int tickPerSecond = 5;

class Projectile : public Entity
{
private:

	

	int framePassed;

	int damage;
	TileType shooterTileType; //used to know who shot (the sheriff)

	void CheckForCollision();
	void CheckTileForCollision(int x, int y);

public:
	Projectile(int x, int y, int damage, char character, Direction dir, std::vector<Tile*>& tiles, TileType shooterTileType);
	~Projectile();

	int GetDamage() { return damage; }

	// Hérité via Entity
	virtual void Die() override;
	virtual void Update() override;
};

