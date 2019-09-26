#pragma once

#include <Windows.h>
#include "Constants.h"
#include "Actor.h"
#include <utility>

const int untouchableFrames = 75;

class Player : public Actor
{
private:
	bool isUntouchable;
	int untouchableFramePassed;

	WORD colorHit;
	WORD colorNormal;

public:
	Player(int x, int y, Direction dir, int health, int damage, char c, std::vector<Tile*>& tiles, TileType type);
	~Player();

	void HandleInput();
	

	void Die() override;
	void Update() override;

	void TakeDamage(int damage) override;

	void Shoot();
};

