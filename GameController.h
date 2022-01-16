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
	int state = 0; //0 -> menu, 1 -> choose of level, 2 -> actual game
	List buttons;
	Vector2 mousePos{ 0,0 };
	char score[MAX_STRING] = {};
	//main menu
	SDL_Surface* mainMenuBackground;
	SDL_Surface* levelMenuBackground;
	SDL_Surface* deathSurface;
	
	int levelNum = 1;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screen;
	SDL_Surface* charset;
	SDL_Surface* healthBar;
	SDL_Surface* numbers[3];

	Player* player;
	bool quit;
	const char* title;
	double delta;
	double worldTime;
	Camera* camera;

	//methods
	void changeState(int x);
	void eventHandler();
	void gameDraw();
public:
	GameController();
	
	void mainMenu();
	void gameState();
	void levelMenu();
	void deathMenu();
	void successMenu();

	void loadMainMenu();
	void loadLevelMenu();
	void loadGameState();
	void loadDeathMenu();
	void loadSuccessMenu();

	void init();
	void load();

	void start();
	//main loop of program
	void update();
	void clean();
};