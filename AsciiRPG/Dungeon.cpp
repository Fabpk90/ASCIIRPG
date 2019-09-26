#include "Dungeon.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Constants.h"
#include "GameManager.h"
#include <time.h>
#include <Windows.h>


std::vector<Tile *>* Dungeon::tiles = nullptr;

int Dungeon::random(int n){
	return rand() % n;
}


/* A modifier */
bool Dungeon::intersect(int x, int y, int size) {
	for (int i = y; i < size - 1; i++) {
		for (int j = x; j < size - 1; j++) {
			if ((*tiles)[i * SCREEN_HEIGHT + j]->character == 'X') {
				return true;
			}
		}
	}
	return false;
}

void Dungeon::getCoordinates(int tile_number, int *x, int *y) {
	
}


void Dungeon::createRectangle(int x, int y, int size, int wall_to_break) {
	for (int i = y; i < y + size; i++) {
		for (int j = x; j < x + size; j++) {
			/*Create an empty room*/
			if (j == x || j == x + size - 1 || i == y || i == y + size - 1) {
				(*tiles)[i * SCREEN_HEIGHT + j]->character = 'X';
				(*tiles)[i * SCREEN_HEIGHT + j]->colorMask = FOREGROUND_RED;
			}

			else {
				(*tiles)[i * SCREEN_HEIGHT + j]->character = ' ';
			}

			/* Creating the door to the next room */
			if (i * SCREEN_HEIGHT + j == wall_to_break) {
				(*tiles)[i * SCREEN_HEIGHT + j]->character = ' ';
			}
		}
	}
}

std::pair<int, int> Dungeon::selectAlmostRandomWall(int x, int y, int size) {
	std::vector<std::pair<int, int>> tab_selectable_walls;
	int random_index = -1;

	for (int i = x + 1; i < x + size - 1; i++) {
		tab_selectable_walls.push_back(std::pair<int, int>(i, y));
		tab_selectable_walls.push_back(std::pair<int, int>(i, y + size - 1));
	}

	for (int j = y + 1; j < y + size - 1; j++) {
		tab_selectable_walls.push_back(std::pair<int, int>(x, j));
		tab_selectable_walls.push_back(std::pair<int, int>(x + size - 1, j));
	}

	random_index = random(tab_selectable_walls.size());
	return tab_selectable_walls[random_index];
}

/* If rectangle, add a size parameter */
/*int Dungeon::selectAlmostRandomWall(int x, int y, int size) {
	std::vector<int> tab_selectable_walls;
	int random_index = -1;

	for (int i = x + 1; i < x + size - 1; i++) {
		tab_selectable_walls.push_back(y * SCREEN_HEIGHT + i);
		tab_selectable_walls.push_back((y + size - 1) * SCREEN_HEIGHT + i);
	}

	for (int j = y + 1; j < y + size - 1; j++) {
		tab_selectable_walls.push_back(j * SCREEN_HEIGHT + x);
		tab_selectable_walls.push_back(j * SCREEN_HEIGHT + (x + size - 1));
	}

	random_index = random(tab_selectable_walls.size());
	return tab_selectable_walls[random_index];
}*/


std::vector<Tile *>* Dungeon::GenAlea(int nb_room) {
	/* Attributes creation */
	nb_room = nb_room;
	tiles = new std::vector<Tile*>(SCREEN_HEIGHT * SCREEN_WIDTH);

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			(*tiles)[i * SCREEN_HEIGHT + j] = new Tile(' ', 0, ENV);
		}
	}

	/*Initializing random generation*/
	srand(time(NULL));

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

	/* Checking if the room can fit in the screen */
	while (random_coord_x + random_size >= SCREEN_HEIGHT || random_coord_y + random_size >= SCREEN_WIDTH) {
		random_coord_x = random(SCREEN_HEIGHT);
		random_coord_y = random(SCREEN_WIDTH);
	}

	//createRectangle(random_coord_x, random_coord_y, random_size);
	//while (i <= nb_room) {
		/* getting random wall coord from the current room */
		
	std::pair<int, int> positionWall = selectAlmostRandomWall(random_coord_x, random_coord_y, random_size);
	
	//wall_break = selectAlmostRandomWall(random_coord_x, random_coord_y, random_size);

		/* Creating the room */
		createRectangle(random_coord_x, random_coord_y, random_size, positionWall.second * SCREEN_HEIGHT + positionWall.first);

		/*getting random size */
		random_size = random(13);

		/*Impossible to walk in a smaller room*/
		if (random_size < 4) {
			random_size = 4;
		}

		/* check collision */
		if (!intersect(random_coord_x, random_coord_y, random_size)) {
			//wall_break = selectAlmostRandomWall(random_coord_x, random_coord_y, random_size);
			positionWall = selectAlmostRandomWall(random_coord_x, random_coord_y, random_size);
			createRectangle(random_coord_x, random_coord_y, random_size, positionWall.second * SCREEN_HEIGHT + positionWall.first);

			// TODO Ecrire fonction d'intersection avec la paire de coordonnées
		}
	//}

		return tiles;
}