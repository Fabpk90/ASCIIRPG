#pragma once

#include "Tile.h"

class Actor : public Tile
{
private:
	int health;
	int damage;

public:
	Actor(int health, int damage, char character, DWORD colorMask);
	~Actor();

	virtual void Die() = 0;
};

