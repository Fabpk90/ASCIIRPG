#pragma once
#include "Tile.h"
#include <vector>

class Dungeon
{
private:
	static std::vector<Tile *> *tiles;
	int center_x;
	int center_y;
	
public:
	Dungeon();
	~Dungeon();
	int random(int n);
	bool intersect(int x, int y, int size);
	void createRectangle(int x, int y, int size);
	void creatingRooms(int nb_rooms);
	void hHallway(int x, int y);
	static std::vector<Tile *>* GenAlea(int nb_room);
};

