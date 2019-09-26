#pragma once

#include <Windows.h>
#include "Constants.h"
#include "Actor.h"
#include <utility>

class Player : public Actor
{

public:
	Player(int x, int y, Direction dir, int health, int damage, char c, std::vector<Tile*>& tiles, TileType type);
	~Player();

	void HandleInput();
	

	void Die() override;
	void Update() override;

	void Shoot();
};

