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
	const char* enemiesFile = "Enemies.csv";
	SDL_Surface* tileset = nullptr;
	int* displayData;
	int* collisionData;
	int* enemyData;
	int dataSize;
	Tile* tiles;
	int tilesSize;
	SDL_Surface* screen;
	List walls;
	List enemies;
	List bullets;
	List playerBullets;
	Player* player;
	Camera* camera;
	Rectangle* cameraCollider;

	SDL_Surface* medKitImg = nullptr;
	bool load(); //0 if cannot load level info
	void horizontalEnemyCollision(GameObject* go);
	void verticalEnemyCollision(GameObject* go);
	bool finished = 0;
	void checkEnemyDeath();
public:
	Level(int width,int height,const char* filePath,const char* tilePath,SDL_Surface* screen,Player* player,Camera* camera);
	//returns a list of game objects that are colliders
	void init();
	void update(Camera* camera,double delta);
	void draw(Camera* camera);
	void horizontalMovementCollision(double delta);
	void verticalMovementCollision(double delta);
	void shoot(double delta);
	void bulletsUpdate(double delta);
	void enemyPlayerCollision();
	bool isFinished();
	List* getPlayerBullets();
};

