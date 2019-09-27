#pragma once

#include "Entity.h"
#include "NYTimer.h"


class Weapon
{
private:
	float cooldownSeconds;

	NYTimer* timer;
	Entity& user;

public:
	Weapon(Entity& user, float cooldownSeconds);

	void Use();

	~Weapon();
};

