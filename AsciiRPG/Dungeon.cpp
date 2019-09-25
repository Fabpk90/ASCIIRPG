#include "Dungeon.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Constants.h"
#include "GameManager.h"
#include <time.h>



Dungeon::Dungeon(int nb_room)
{
	this->nb_room = nb_room;
	this->tiles = new Tile[SCREEN_HEIGHT * SCREEN_WIDTH];

	srand(time(NULL));
}

Dungeon::~Dungeon()
{
	delete[] tiles;
}

int Dungeon::random(int n){
	return rand() % n;
}

/* A modifier */
bool Dungeon::intersect(int x1, int y1, int x2, int y2) {
	return (x1 <= x2 && x2 >= x1 && y1 <= y2 && y2 >= y1);
}

void Dungeon::drawRectangle(int x, int y, int size) {
	for (int i = y; i < y + size; i++) {
		for (int j = x; j < x + size; j++) {
			
			/*Create an empty room*/
			if (j == x || j == x + size - 1 || i == y || i == y + size - 1) {
				std::cout << 'X';
				this->tiles[y * SCREEN_HEIGHT + x].character = 'X';
				this->tiles[y * SCREEN_HEIGHT + x].mask = FOREGROUND_BLUE;
			}
			
			else {
				std::cout << ' ';
				this->tiles[y * SCREEN_HEIGHT + x].character = ' ';
			}
		}
		std::cout << std::endl;
	}
}

/* If rectangle, add a size parameter */
int Dungeon::selectAlmostRandomWall(int x, int y, int size) {
	std::vector<int> tab_selectable_walls;
	int random_index = -1;

	for (int i = x + 1; i < x + size - 2; i++) {
		tab_selectable_walls.push_back(y * SCREEN_HEIGHT + x);
		tab_selectable_walls.push_back(y + size - 2 * SCREEN_HEIGHT + x);
	}

	for (int j = y + 1; j < y + size - 2; j++) {
		tab_selectable_walls.push_back(y * SCREEN_HEIGHT + x);
		tab_selectable_walls.push_back(y * SCREEN_HEIGHT + x + size - 2);
	}

	random_index = random(tab_selectable_walls.size());
	std::cout << tab_selectable_walls[random_index] << std::endl;
	return tab_selectable_walls[random_index];
	
}


void Dungeon::GenAlea() {
	int random_size = 12;
	int random_coord_x = 0;
	int random_coord_y = 0;

	int wall_break = 0;
	

	/* Standard size for every kind of room :
	Big : 12*12 (100 tiles for move)
	Medium : 8*8 (36 tiles for move)
	Small : 6*6 (16 tiles for move) */

	/* Generating random coord for the first room*/
	random_coord_x = random(SCREEN_HEIGHT);
	random_coord_y = random(SCREEN_WIDTH);
	random_size = random(13);

	/*Impossible to walk in a smaller room*/
	if (random_size < 4) {
		random_size = 4;
	}

	this->drawRectangle(random_coord_x, random_coord_y, random_size);

	/* While i != nb_room */
	/* getting random wall coord from the current room */
	wall_break = selectAlmostRandomWall(random_coord_x, random_coord_y, random_size);
	
	/*Changing tiles to make a X become ' ' */
	this->tiles[wall_break].character = ' ';

	//drawRectangle(random_coord_x, random_coord_y, random_size);
	/*getting random size */
	random_size = random(13);

	/*Impossible to walk in a smaller room*/
	if (random_size < 4) {
		random_size = 4;
	}

	/* check collision */
	/*if (!intersect()) {
		drawRectangle(random_coord_x, random_coord_y, random_size);
	}*/

	/* Return a Tile matrice*/
}