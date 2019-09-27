#pragma once

#include <vector>
#include "Tile.h"

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum PositionBlocked
{
	OUT_OF_BOUND,
	OBSTACLE,
	NOT_BLOCKED
};

class Entity : public Tile
{
protected:
	std::vector<Tile*>& tiles;
	int x;
	int y;
	Direction dir;

	bool isActive;
public:
	Entity(int x, int y, Direction dir, std::vector<Tile*>& tiles, char character, WORD colorMask, TileType type);
	~Entity();

	int GetX() { return x; }
	int GetY() { return y; }

	Direction GetDirection() { return dir; }
	std::vector<Tile*>& GetTiles() { return tiles; }

	bool GetIsActive() { return isActive; }

	virtual void Die() = 0;
	virtual void Update() = 0;

	virtual PositionBlocked ChangePosition(int x, int y);
	std::pair<int, int> GetPositionFromDirection();
};

