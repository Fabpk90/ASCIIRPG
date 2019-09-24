#pragma once

#include <Windows.h>
#include "Constants.h"
#include "Actor.h"

class Player : public Actor
{

public:
	Player(int x, int y, int health, int damage, char c, Tile **tiles);
	~Player();

	int GetX() { return x; }
	int GetY() { return y; }

	void HandleInput();
	bool ChangePosition(int x, int y);
	bool AttackAt(int x, int y);

	void Die() override;
	void Update() override;
};

