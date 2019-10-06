#pragma once
#include "Tile.h"
#include <vector>

class Dungeon
{
private:
	int nb_room;
	Tile* tiles;

	static void GenRandomWalls(std::vector<char> &tiles);
	static void GenWallAround(std::vector<char>& finalTiles);
public:
	Dungeon(int nb_room);
	~Dungeon();
	int random(int n);
	bool intersect(int x1, int y1, int x2, int y2);
	void drawRectangle(int x, int y, int size);
	int selectAlmostRandomWall(int x, int y, int size);
	void GenAlea();

	//Assumes that the vector passed in has a SCREENX * SCREENY size
	static void GenCave(int iterations, std::vector<Tile*>& finalTiles);
	
};

