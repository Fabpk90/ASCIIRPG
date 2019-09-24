#include "Tile.h"

Tile::Tile()
{
	character = ' ';
	colorMask = 0;
}

Tile::Tile(char character, WORD colorMask) : character(character), colorMask(colorMask)
{}


Tile::~Tile()
{
}

bool Tile::isObstacle()
{
	return character == ' ' ? false : true;
}
