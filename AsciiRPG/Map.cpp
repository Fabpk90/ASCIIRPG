#include "Map.h"

#include <iostream>
#include <fstream>


#include "GameManager.h"
#include "Dungeon.h"

#include <map>

Map::Map(const char * path)
{
	buffer = new CHAR_INFO[SCREEN_HEIGHT * SCREEN_WIDTH];
	tiles = std::vector<Tile*>(SCREEN_HEIGHT * SCREEN_WIDTH);
	

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			tiles[i * SCREEN_HEIGHT + j] = GameManager::GetInstance().groundTile;
		}
	}

	//sert � init le buffer
	ReadConsoleOutput(GameManager::GetInstance().handleOutput, (CHAR_INFO*)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

	LoadMap(path);

	player = new Player(2, 2, DOWN, 30, 2, '@', tiles, TileType::PLAYER);
	//Dungeon::GenCave(3, tiles, *player, entities);
	
	hud = new HUD(10, 50, 3, *player);

	entities.push_back(player);

	
}

Map::~Map()
{
	delete player;
	delete[] buffer;
	delete hud;
	
	for (Tile* t : tiles)
	{
		delete t;
	}
	for (Entity* a : entities)
	{
		delete a;
	}

}

void Map::Draw()
{
	for (Entity* a : entities)
	{
		if (a->GetIsActive())
			a->Update();
	}

	//checks each frame if actors are to be added
	if (!entitiesToAdd.empty())
	{
		for (Entity* ent : entitiesToAdd)
		{
			entities.push_back(ent);
		}
		entitiesToAdd.clear();
	}


	//checks each frame if actors are to be deleted
	if (!entitiesToDestroy.empty())
	{
		for (Entity* index : entitiesToDestroy)
		{
			int indexToDelete = -1;
			//dirty hax to know the indesx of the actor to be deleted
			for (int i = 0; i < entities.size() && indexToDelete == -1; i++)
			{
				if (entities[i] == index)
					indexToDelete = i;
			}

			//setting back the ground
			int x = entities[indexToDelete]->GetX();
			int y = entities[indexToDelete]->GetY();
			tiles[y * SCREEN_HEIGHT + x] = GameManager::GetInstance().groundTile;

			//deleting effectively the entity
			delete entities[indexToDelete];
			entities.erase(entities.begin() + indexToDelete);
		}

		entitiesToDestroy.clear();
	}

	hud->Draw();
	
	UpdateBuffer();

	WriteConsoleOutput(GameManager::GetInstance().handleOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Map::UpdateBuffer()
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			buffer[i * SCREEN_HEIGHT + j].Attributes = tiles[i * SCREEN_HEIGHT + j]->colorMask;

			if (tiles[i * SCREEN_HEIGHT + j]->type == PLAYER 
				|| tiles[i * SCREEN_HEIGHT + j]->type == ENEMY)
			{
				buffer[i * SCREEN_HEIGHT + j].Char.UnicodeChar = tiles[i * SCREEN_HEIGHT + j]->character;
			}
			else
				buffer[i * SCREEN_HEIGHT + j].Char.AsciiChar = tiles[i * SCREEN_HEIGHT + j]->character;
			
		}
	}
}

//called by an actor when he dies
void Map::EntityDies(Entity * ent)
{
	entitiesToDestroy.push_back(ent);
}

void Map::AddEntity(Entity * ent)
{
	entitiesToAdd.push_back(ent);
}

void Map::ResetMap()
{
	//clears all the actors because we are loading another map
	for (Entity* a : entities)
	{
		//TODO: find a better solution
		if (auto p = dynamic_cast<Player*>(a))
		{
		}
		else
		{
			delete a;
		}
	}

	entities.clear();

	//resets the tiles
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			tiles[i * SCREEN_HEIGHT + j] = GameManager::GetInstance().groundTile;
		}
	}
}

//Generates a map from the dungeonGenerator
void Map::LoadMap()
{
	ResetMap();

	Dungeon::GenCave(3, tiles, *player, entities);
	
	entities.push_back(player);
}

void Map::LoadMap(const char * path)
{

	//TODO: it'd nice to find a better solution than pushing into a vector
	
	std::ifstream stream(path);

	if (!stream.fail())
	{

		ResetMap();

		std::string str;
		
		int width = 0;
		int height = 0;

		//reads line by line the map
		while (std::getline(stream, str))
		{
			width = 0;
			for (int i = 0; i < str.length(); i++)
			{
				switch (str[i])
				{
				case ' ':
					buffer[height * SCREEN_HEIGHT + width].Char.AsciiChar = GameManager::GetInstance().groundTile->character;
					buffer[height * SCREEN_HEIGHT + width].Attributes = GameManager::GetInstance().groundTile->colorMask;

					tiles[height * SCREEN_HEIGHT + width] = (GameManager::GetInstance().groundTile);
					break;

				case 'X':
					buffer[height * SCREEN_HEIGHT + width].Char.AsciiChar = GameManager::GetInstance().wallTile->character;
					buffer[height * SCREEN_HEIGHT + width].Attributes = GameManager::GetInstance().wallTile->colorMask;
					
					tiles[height * SCREEN_HEIGHT + width] = (GameManager::GetInstance().wallTile);
					break;

				case 'E':
					buffer[height * SCREEN_HEIGHT + width].Char.AsciiChar = GameManager::GetInstance().exitTile->character;
					buffer[height * SCREEN_HEIGHT + width].Attributes = GameManager::GetInstance().exitTile->colorMask;

					tiles[height * SCREEN_HEIGHT + width] = (GameManager::GetInstance().exitTile);
					break;
				}

				width++;
			}
			height++;
		}
		stream.close();
	}
}
