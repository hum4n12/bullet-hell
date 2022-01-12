#pragma once
#include "List.h"
#include "Tile.h"
#include "GLOBALS.h"
#include "./SDL2-2.0.10/include/SDL.h"
#include "Camera.h"
#include <vector>
#define NUMBER_OF_TILES 8
#define NUMBER_OF_TILES_PER_ROW 5
#define MAX_PATH_LENGTH 30

class Level{
private:
	int width; //width in tiles (*64 to get pixel width)
	int height;//height in tiles (*64 to get pixel height)
	const char* filePath;
	const char* tileSetPath;
	const char* base = "Base.csv";
	const char* colliders = "Colliders.csv";
	int* displayData;
	int* collisionData;
	int dataSize;
	Tile* tiles;
	int tilesSize;
	SDL_Surface* screen;
	List gameObjects;
	List walls;
	Player* player;
	bool load(); //0 if cannot load level info
public:
	Level(int width,int height,const char* filePath,const char* tilePath,SDL_Surface* screen,Player* player);
	//returns a list of game objects that are colliders
	void init();
	void update(Camera* camera,double delta);
	void draw(Camera* camera);
	void horizontalMovementCollision(double delta);
	void verticalMovementCollision(double delta);
};

