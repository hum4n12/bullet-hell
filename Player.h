#pragma once
#include "GameObject.h"
#include "GLOBALS.h"
#include "Camera.h"
#include "Rectangle.h"
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

class Player :public GameObject{
private:
	Camera* camera;
	int const CONST_SPEED = 700;
public:
	int posX = 0;
	int posY = 0;
	Player(Camera* camera,ColliderShape* shape, SDL_Surface* image = nullptr);
	void controls(SDL_Event event);
	void setX(int x);
	void setY(int y);
	void update(int offsetX,int offsetY, double delta = 0) override;
};

