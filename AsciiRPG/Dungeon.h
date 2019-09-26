#pragma once
#include "Tile.h"
#include <vector>

class Dungeon
{
private:
	static std::vector<Tile *> *tiles;

	//Tile & getTiles();

	static int random(int n);
	static bool intersect(int x, int y, int size);
	void getCoordinates(int tile_number, int * x, int * y);
	static void createRectangle(int x, int y, int size, int wall_to_break);
	static std::pair<int, int> selectAlmostRandomWall(int x, int y, int size);

public:

	static std::vector<Tile *>* GenAlea(int nb_room);
};

