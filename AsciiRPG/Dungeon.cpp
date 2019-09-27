#include "Dungeon.h"
#include "Constants.h"

#include <time.h>
#include <>



Dungeon::Dungeon()
{
	this->center_x = 0;
	this->center_y = 0;
}


Dungeon::~Dungeon()
{
}

int Dungeon::random(int n) {
	return rand() % n;
}

bool Dungeon::intersect(int x, int y, int size) {
	if (x + size > SCREEN_WIDTH || y + size > SCREEN_HEIGHT) {
		return true;
	}
	for (int i = y; i < size - 1; i++) {
		for (int j = x; j < size - 1; j++) {
			if ((*tiles)[i * SCREEN_HEIGHT + j]->character == 'X') {
				return true;
			}
		}
	}
	return false;
}

void Dungeon::createRectangle(int x, int y, int size) {
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
			if ( ??? ) {
				(*tiles)[i * SCREEN_HEIGHT + j]->character = ' ';
			}
		}
	}
}

void Dungeon::creatingRooms(int nb_rooms) {
	std::vector<std::pair<int, int>> rooms;
	for (int i = 0; i < nb_rooms; i++) {
		int random_size = 12;
		int random_coord_x = 0;
		int random_coord_y = 0;

		/* Generating random coord and size for the first room*/
		random_coord_x = random(SCREEN_HEIGHT);
		random_coord_y = random(SCREEN_WIDTH);

		random_size = random(13);

		/*Impossible to walk in a smaller room*/
		if (random_size < 4) {
			random_size = 4;
		}

		if (!intersect(random_coord_x, random_coord_y, random_size)) {
			createRectangle(random_coord_x, random_coord_y, random_size);
			rooms.push_back();
		}

	}
}

void Dungeon::hHallway(int x, int y) {

}

std::vector<Tile*>* Dungeon::GenAlea(int nb_room)
{
	tiles = new std::vector<Tile*>(SCREEN_HEIGHT * SCREEN_WIDTH);

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			(*tiles)[i * SCREEN_HEIGHT + j] = new Tile(' ', 0, ENV);
		}
	}

	/*Initializing random generation*/
	srand(time(NULL));

	

	/* Checking if the room can fit in the screen */
	while (random_coord_x + random_size >= SCREEN_HEIGHT || random_coord_y + random_size >= SCREEN_WIDTH) {
		random_coord_x = random(SCREEN_HEIGHT);
		random_coord_y = random(SCREEN_WIDTH);
	}


	return tiles;
}