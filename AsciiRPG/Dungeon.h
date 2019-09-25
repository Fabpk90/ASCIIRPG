#pragma once
#include "Tile.h"

class Dungeon
{
private:
	int nb_room;
	Tile* tiles;

public:
	Dungeon(int nb_room);
	~Dungeon();
	int random(int n);
	bool intersect(int x1, int y1, int x2, int y2);
	void drawRectangle(int x, int y, int size);
	int selectAlmostRandomWall(int x, int y, int size);
	void GenAlea();
};

