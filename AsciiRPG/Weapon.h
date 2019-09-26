#pragma once

#include "Entity.h"


class Weapon
{
private:
	unsigned int timeSinceLastUse;
	unsigned int cooldown;
public:
	Weapon(int cooldown);


	void Use(Entity& user);

	~Weapon();
};

