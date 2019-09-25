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
	

	void Die() override;
	void Update() override;
};

