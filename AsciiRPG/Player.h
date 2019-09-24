#pragma once

#include <Windows.h>
#include "Constants.h"
#include "Actor.h"

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Player : public Actor
{
private:
	int x;
	int y;

	Direction dir;


public:
	Player(int health, int damage, char c);
	~Player();

	int GetX() { return x; }
	int GetY() { return y; }

	void HandleInput();
	bool ChangePosition(int x, int y);
	bool AttackAt(int x, int y);

	void Die() override;

	Tile **tiles;
};

