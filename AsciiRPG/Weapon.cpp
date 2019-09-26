#include "Weapon.h"

Weapon::Weapon(int cooldown) : cooldown(cooldown)
{
	timeSinceLastUse = 0;
}

void Weapon::Use(Entity & user)
{
}

Weapon::~Weapon()
{
}
