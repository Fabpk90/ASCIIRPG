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


//An Entity can be moved, updated and die
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
	virtual ~Entity();

	int GetX() const { return x; }
	int GetY() const { return y; }

	Direction GetDirection() const { return dir; }
	std::vector<Tile*>& GetTiles() { return tiles; }

	bool GetIsActive() const { return isActive; }

	virtual void Die() = 0;
	virtual void Update() = 0;

	// Returns the type of blockage, could be none
	virtual PositionBlocked ChangePosition(int x, int y);
	std::pair<int, int> GetPositionFromDirection();
};

