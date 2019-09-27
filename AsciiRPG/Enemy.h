#pragma once

#include "Actor.h"
#include "Weapon.h"

const int frameBeforeTick = 8;

class Enemy : public Actor
{
private:
	int framePassed;
	
	Weapon* weapon;

public:
	Enemy(int x, int y, Direction dir, int health, int damage, char c, WORD colorMask, std::vector<Tile*>& tiles);
	~Enemy();

	// Hérité via Actor
	virtual void Die() override;
	virtual void Update() override;

	void FollowTarget();

};

