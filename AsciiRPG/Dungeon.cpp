#include "Dungeon.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Constants.h"
#include "GameManager.h"
#include <time.h>
#include <Windows.h>


std::vector<Tile *>* Dungeon::tiles = nullptr;


/*Dungeon::Dungeon(int nb_room)
{
}

Dungeon::~Dungeon()
{
	delete[] tiles;
}*/

/*Tile & Dungeon::getTiles()
{
	return *tiles;
}*/

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
				
				(*tiles)[y * SCREEN_HEIGHT + x]->character = 'X';
				(*tiles)[y * SCREEN_HEIGHT + x]->colorMask = FOREGROUND_BLUE;
			}
			
			else {
				(*tiles)[y * SCREEN_HEIGHT + x]->character = ' ';
			}
		}
	}
}

/* If rectangle, add a size parameter */
int Dungeon::selectAlmostRandomWall(int x, int y, int size) {
	std::vector<int> tab_selectable_walls;
	int random_index = -1;

	for (int i = x + 1; i < x + size - 1; i++) {
		tab_selectable_walls.push_back(y * SCREEN_HEIGHT + x);
		tab_selectable_walls.push_back((y + size - 1) * SCREEN_HEIGHT + x);
	}

	for (int j = y + 1; j < y + size - 1; j++) {
		tab_selectable_walls.push_back(y * SCREEN_HEIGHT + x);
		tab_selectable_walls.push_back(y * SCREEN_HEIGHT + (x + size - 1));
	}

	random_index = random(tab_selectable_walls.size());
	return tab_selectable_walls[random_index];
	
}


std::vector<Tile *>* Dungeon::GenAlea(int nb_room) {
	/* Attributes creation */

	nb_room = nb_room;
	tiles = new std::vector<Tile*>(SCREEN_HEIGHT * SCREEN_WIDTH);

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			(*tiles)[i * SCREEN_HEIGHT + j] = new Tile('.', 0, ENV);
		}
	}

	srand(time(NULL));

	/*Initializing variables for the random generation*/

	int random_size = 12;
	int random_coord_x = 0;
	int random_coord_y = 0;

	int wall_break = 0;

	int i = 0;


	/* Generating random coord and size for the first room*/
	random_coord_x = random(SCREEN_HEIGHT);
	random_coord_y = random(SCREEN_WIDTH);
	random_size = random(13);

	/*Impossible to walk in a smaller room*/
	if (random_size < 4) {
		random_size = 4;
	}

	drawRectangle(random_coord_x, random_coord_y, random_size);

	//while (i <= nb_room) {
		/* getting random wall coord from the current room */
		wall_break = selectAlmostRandomWall(random_coord_x, random_coord_y, random_size);

		/*Changing tiles to make a X become ' ' */
		//tiles[wall_break]->character = ' ';

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
	//}

		return tiles;
}