#pragma once

#include "./SDL2-2.0.10/include/SDL.h"
#include "Graphics.h"
#include "GameObject.h"
#include "Player.h"
#include "Rectangle.h"
#include "List.h"
#include "Level.h"
#include "GLOBALS.h"
#include "Camera.h"

class GameController {
private:
	bool gameStarted = false;
	Level* currentLevel;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screen;
	Player* player;
	bool quit;
	const char* title;
	double delta;
	double worldTime;
	Camera* camera;
	//methods
	void eventHandler();
public:
	GameController();
	void init();
	void start();
	//main loop of program
	void update();
	void clean();
};