#include "Dungeon.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Constants.h"
#include "GameManager.h"
#include <ctime>





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
				this->tiles[y * SCREEN_HEIGHT + x].colorMask = FOREGROUND_BLUE;
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

void Dungeon::GenRandomWalls(std::vector<char>& tiles)
{
	std::srand(time(NULL));

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			if (std::rand() % 101 <= 65)
				tiles[i * SCREEN_HEIGHT + j] = 'X';
			else
			{
				tiles[i * SCREEN_HEIGHT + j] = ' ';
			}
		}
	}
}

void Dungeon::GenCave(int iterations, std::vector<Tile*>& finalTiles, Player& player)
{
	int wallCount;
	//used to store the matrix when is being modified
	//so that the algorithm modify generation by generation the map

	std::vector<char> tiles = std::vector<char>(SCREEN_HEIGHT * SCREEN_WIDTH);
	GenRandomWalls(tiles);

	std::vector<char> tilesBeingModified = tiles;

	char wallCharacter = 'X';

	for (int iter = 0; iter < iterations; iter++)
	{
		for (int i = 0; i < SCREEN_HEIGHT; i++)
		{
			for (int j = 0; j < SCREEN_WIDTH; j++)
			{
				wallCount = 0;
				if (i - 2 >= 0 && i + 2 <= SCREEN_HEIGHT - 1 && j - 2 >= 0 && j + 2 <= SCREEN_WIDTH - 1) // check for array boundaries
				{
					//we count surrounding walls, 8 cells
					// applying 4-5 rule
					if (tiles[(i - 1) * SCREEN_HEIGHT + j] == wallCharacter)
						wallCount++;
					if (tiles[(i + 1) * SCREEN_HEIGHT + j] == wallCharacter)
						wallCount++;
					if (tiles[(i - 2) * SCREEN_HEIGHT + j] == wallCharacter)
						wallCount++;
					if (tiles[(i + 2) * SCREEN_HEIGHT + j] == wallCharacter)
						wallCount++;
					if (tiles[i * SCREEN_HEIGHT + j + 1] == wallCharacter)
						wallCount++;
					if (tiles[i * SCREEN_HEIGHT + j - 1] == wallCharacter)
						wallCount++;
					if (tiles[i * SCREEN_HEIGHT + j + 2] == wallCharacter)
						wallCount++;
					if (tiles[i * SCREEN_HEIGHT + j - 2] == wallCharacter)
						wallCount++;

					if (tiles[i * SCREEN_HEIGHT + j] == wallCharacter)
					{
						//we check according to the rule
						if (wallCount >= 5 || wallCount <= 1)
						{
							tilesBeingModified[i * SCREEN_HEIGHT + j] = wallCharacter;
						}
						else
						{
							tilesBeingModified[i * SCREEN_HEIGHT + j] = ' ';
						}
					}
					else if (tiles[i * SCREEN_HEIGHT + j] == wallCharacter)
					{
						if (wallCount > 5)
							tilesBeingModified[i * SCREEN_HEIGHT + j] = wallCharacter;
					}


				} //make the edges walls
				else if (i == 0 || i + 1 == SCREEN_HEIGHT || j == 0 || j + 1 == SCREEN_WIDTH)
					tiles[i * SCREEN_HEIGHT + j] = wallCharacter;
			}
		}

		tiles = tilesBeingModified;
	}

	GenWallAround(tiles);
	GenExit(tiles);

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			if (tiles[i * SCREEN_HEIGHT + j] == wallCharacter)
				finalTiles[i * SCREEN_HEIGHT + j] = GameManager::GetInstance().wallTile;
			else if (tiles[i * SCREEN_HEIGHT + j] == 'E')
				finalTiles[i * SCREEN_HEIGHT + j] = GameManager::GetInstance().exitTile;
			else
				finalTiles[i * SCREEN_HEIGHT + j] = GameManager::GetInstance().groundTile;
		}
	}

	GenPlayerPosition(player, tiles);
}

void Dungeon::GenWallAround(std::vector<char>& finalTiles)
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			if (i == 0 || i == SCREEN_HEIGHT - 1 
				|| j == 0 || j == SCREEN_WIDTH - 1)
			{
				finalTiles[i * SCREEN_HEIGHT + j] = 'X';
			}
		}
	}
}

void Dungeon::GenPlayerPosition(Player& player, std::vector<char>& tiles)
{
	//copy pasted in this case
	//but useful if a different technique is needed for the player position (from the goal's one)
	
	int x = 0;
	int y = 0;

	std::srand(std::time(nullptr));

	do
	{
		x = std::rand() % SCREEN_WIDTH;
		y = std::rand() % SCREEN_HEIGHT;
	} while (!AreNeighboorsCellsFree(tiles, x, y));

	player.SetPosition(x, y);
}

void Dungeon::GenExit(std::vector<char>& tiles)
{
	int x = 0;
	int y = 0;

	std::srand(std::time(nullptr));

	do
	{
		x = std::rand() % SCREEN_WIDTH;
		y = std::rand() % SCREEN_HEIGHT;
	}
	while (!AreNeighboorsCellsFree(tiles, x, y));

	tiles[y * SCREEN_HEIGHT + x] = 'E';
}

bool Dungeon::AreNeighboorsCellsFree(std::vector<char>& tiles, int x, int y)
{
	//checking the 9 cells
	
	if (tiles[y * SCREEN_HEIGHT + x] != ' ') return false;
	if (tiles[(y - 1) * SCREEN_HEIGHT + x - 1] != ' ') return false;
	if (tiles[(y - 1) * SCREEN_HEIGHT + x] != ' ') return false;
	if (tiles[(y - 1) * SCREEN_HEIGHT + x + 1] != ' ') return false;
	if (tiles[(y) * SCREEN_HEIGHT + x - 1] != ' ') return false;
	if (tiles[(y) * SCREEN_HEIGHT + x + 1] != ' ') return false;
	if (tiles[(y + 1) * SCREEN_HEIGHT + x - 1] != ' ') return false;
	if (tiles[(y + 1) * SCREEN_HEIGHT + x] != ' ') return false;
	if (tiles[(y + 1) * SCREEN_HEIGHT + x + 1] != ' ') return false;
	

	return true;
}