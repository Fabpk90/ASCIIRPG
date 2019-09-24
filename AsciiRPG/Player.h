#pragma once

#include <Windows.h>
#include "Constants.h"
#include "Actor.h"
#include <utility>

class Player : public Actor
{
private:
	std::pair<int, int> GetPositionFromDirection();

public:
	Player(int x, int y, int health, int damage, char c, std::vector<Tile*>& tiles, TileType type);
	~Player();

	void HandleInput();
	bool ChangePosition(int x, int y);
	bool AttackAt(int x, int y);

	void Die() override;
	void Update() override;
};

