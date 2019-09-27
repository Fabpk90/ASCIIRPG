#include "Tile.h"

Tile::Tile()
{
	character = ' ';
	colorMask = 0;
	type = ENV;
}

Tile::Tile(wchar_t character, WORD colorMask, TileType type) : character(character), colorMask(colorMask), type(type)
{}


Tile::~Tile()
{
}

bool Tile::isObstacle()
{
	return character == ' ' ? false : true;
}
