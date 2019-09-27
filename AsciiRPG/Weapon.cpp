#include "Weapon.h"
#include "Constants.h"
#include "GameManager.h"
#include "Projectile.h"

Weapon::Weapon(Entity& user, float cooldownSeconds) : cooldownSeconds(cooldownSeconds), user(user)
{
	timer = new NYTimer();
	timer->start();
}

void Weapon::Use()
{
	if (timer->getElapsedSeconds() >= cooldownSeconds)
	{
		timer->start();

		std::pair<int, int> position = user.GetPositionFromDirection();

		if (position.first > 0 && position.first < SCREEN_WIDTH
			&& position.second > 0 && position.second < SCREEN_HEIGHT)
		{
			GameManager::GetInstance().m->AddEntity(
				new Projectile(position.first, position.second, 2, '*', user.GetDirection(), user.GetTiles(), user.type));
		}
	}
}

Weapon::~Weapon()
{
	delete timer;
}
