#include "Entity.h"

#include "Constants.h"
#include "GameManager.h"


Entity::Entity(int x, int y, Direction dir, std::vector<Tile*>& tiles, char character, WORD colorMask, TileType type)
	: x(x), y(y), tiles(tiles), dir(dir), isActive(true), Tile(character, colorMask, type)
{}

Entity::~Entity()
{
}

PositionBlocked Entity::ChangePosition(int x, int y)
{
	//out of bound
	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_WIDTH)
		return OUT_OF_BOUND;

	if (!(tiles[y * SCREEN_HEIGHT + x])->isObstacle())
	{
		tiles[this->y * SCREEN_HEIGHT + this->x] = GameManager::GetInstance().ground;

		tiles[y * SCREEN_HEIGHT + x] = this;

		//updating the direction
		int diffY = this->y - y;
		int diffX = this->x - x;

		if (diffY > 0)
			dir = UP;
		else if (diffY < 0)
			dir = DOWN;
		else if (diffX > 0)
			dir = LEFT;
		else if (diffX < 0)
			dir = RIGHT;

		this->y = y;
		this->x = x;

		return NOT_BLOCKED;
	}

	return OBSTACLE;
}

std::pair<int, int> Entity::GetPositionFromDirection()
{
	std::pair<int, int> position;
	switch (dir)
	{
	case UP:
		position.first = x;
		position.second = y - 1;
		break;

	case RIGHT:
		position.first = x + 1;
		position.second = y;
		break;

	case DOWN:
		position.first = x;
		position.second = y + 1;
		break;

	case LEFT:
		position.first = x - 1;
		position.second = y;
		break;
	default:
		break;
	}

	return position;
}
