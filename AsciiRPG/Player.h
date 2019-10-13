#pragma once

#include <Windows.h>
#include "Constants.h"
#include "Actor.h"
#include <utility>

#include "Weapon.h"
#include "NYTimer.h"

const float untouchableTime = 1.5f;

class Player : public Actor
{
private:
	bool isUntouchable;

	WORD colorHit;
	WORD colorNormal;

	Weapon *weapon;
	NYTimer* timer;

public:
	Player(int x, int y, Direction dir, int health, int damage, char c, std::vector<Tile*>& tiles, TileType type);
	~Player();

	void HandleInput();
	

	void Die() override;
	void Update() override;

	PositionBlocked ChangePosition(int x, int y) override;
	void SetPosition(int x, int y);

	void TakeDamage(int damage) override;

	void Shoot();
};

