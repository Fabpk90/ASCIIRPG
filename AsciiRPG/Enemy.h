#pragma once

#include "Actor.h"

class Enemy : public Actor
{
private:
	int health;
	int damage;

	int framePassed;
	const int frameBeforeTick = 120;

public:
	Enemy(int x, int y, Direction dir, int health, int damage, char c, WORD colorMask, std::vector<Tile*>& tiles);
	~Enemy();

	// H�rit� via Actor
	virtual void Die() override;
	virtual void Update() override;

	void FollowTarget();

};

