#include "Dungeon.h"
#include <cstdlib>
#include <vector>
#include "Constants.h"
#include "GameManager.h"
#include <ctime>



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

void Dungeon::GenCave(int iterations, std::vector<Tile*>& finalTiles, Player& player, std::vector<Entity*>& entities)
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
	GenPlayerPosition(player, tiles);

	finalTiles[player.GetY() * SCREEN_HEIGHT + player.GetX()] = &player;

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

	GenEnemies(finalTiles, entities);
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

void Dungeon::GenEnemies(std::vector<Tile* >& tiles, std::vector<Entity*>& entities)
{
	int enemiesToSpawn = (GameManager::GetInstance().GetLevel() + 1) * 2;

	int x = 0;
	int y = 0;

	std::srand(std::time(nullptr));
	
	for (int enemiesSpawned = 0; enemiesSpawned != enemiesToSpawn; enemiesSpawned++)
	{
		do
		{
			x = std::rand() % SCREEN_WIDTH;
			y = std::rand() % SCREEN_HEIGHT;
		} while (!AreNeighboorsCellsFree(tiles, x, y));

		Entity* enemy = new Enemy(x, y, DOWN, 5, 2, 'A', FOREGROUND_RED, tiles);
		tiles[y * SCREEN_HEIGHT + x] = enemy;
		entities.push_back(enemy);
	}
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

bool Dungeon::AreNeighboorsCellsFree(std::vector<Tile*>& tiles, int x, int y)
{
	//checking the 9 cells

	if (tiles[y * SCREEN_HEIGHT + x]->character != ' ') return false;
	if (tiles[(y - 1) * SCREEN_HEIGHT + x - 1]->character != ' ') return false;
	if (tiles[(y - 1) * SCREEN_HEIGHT + x]->character != ' ') return false;
	if (tiles[(y - 1) * SCREEN_HEIGHT + x + 1]->character != ' ') return false;
	if (tiles[(y)*SCREEN_HEIGHT + x - 1]->character != ' ') return false;
	if (tiles[(y)*SCREEN_HEIGHT + x + 1]->character != ' ') return false;
	if (tiles[(y + 1) * SCREEN_HEIGHT + x - 1]->character != ' ') return false;
	if (tiles[(y + 1) * SCREEN_HEIGHT + x]->character != ' ') return false;
	if (tiles[(y + 1) * SCREEN_HEIGHT + x + 1]->character != ' ') return false;


	return true;
}