#pragma once

#include "Constants.h"
#include <string>
#include <windows.h>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "Entity.h"

#include "HUD.h"

class Map
{

private:
	CHAR_INFO* buffer;
	
	Player* player;
	Enemy* enemy;

	std::vector<Entity*> entities;

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	std::vector<Tile*> tiles;
	std::vector<Entity* > entitiesToDestroy;
	std::vector<Entity*> entitiesToAdd;

	HUD* hud;

	void UpdateBuffer();
	void ResetMap();
	

public:
	Map(const char* path);
	~Map();

	void Draw();

	Player& GetPlayer() { return *player; }

	void EntityDies(Entity* ent);
	void AddEntity(Entity* ent);
	

	//Assumes that the size doesn't change
	void LoadMap(const char *path);

	//Generating a procedural cave
	void LoadMap();
};

