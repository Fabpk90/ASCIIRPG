#pragma once
#include "Tile.h"
#include <vector>

#include "Player.h"

class Dungeon
{
private:
	int nb_room;
	Tile* tiles;

	static void GenRandomWalls(std::vector<char> &tiles);
	static void GenWallAround(std::vector<char>& finalTiles);
	static void GenPlayerPosition(Player& player, std::vector<char>& tiles);
	static void GenExit(std::vector<char>& finalTiles);
	static void GenEnemies(std::vector<Tile*>& tiles, std::vector<Entity*>& entities);
	static bool AreNeighboorsCellsFree(std::vector<char>& tiles, int x, int y);
	static bool AreNeighboorsCellsFree(std::vector<Tile*>& tiles, int x, int y);
public:
	Dungeon(int nb_room);
	~Dungeon();
	int random(int n);
	bool intersect(int x1, int y1, int x2, int y2);
	void drawRectangle(int x, int y, int size);
	int selectAlmostRandomWall(int x, int y, int size);
	void GenAlea();

	//Assumes that the vector passed in has a SCREENX * SCREENY size
	static void GenCave(int iterations, std::vector<Tile*>& finalTiles, Player& player, std::vector<Entity*>& entities);
	
};

