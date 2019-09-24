#pragma once

#include "Actor.h"

class Enemy : public Actor
{
private:
	int health;
	int damage;

public:
	Enemy(int x, int y, int health, int damage, char c, WORD colorMask, Tile **tiles);
	~Enemy();

	bool isObstacle() override;

	// H�rit� via Actor
	virtual void Die() override;
	virtual void Update() override;

};

