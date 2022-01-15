#pragma once
#include "GameObject.h"
#include "GLOBALS.h"
#include "Camera.h"
#include "Rectangle.h"
#include "List.h"
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

class Player :public GameObject{
private:
	Camera* camera;
	List* bullets;
	int const CONST_SPEED = 650;
public:
	int posX = 0;
	int posY = 0;
	Player(Camera* camera,ColliderShape* shape, SDL_Surface* image = nullptr);
	void controls(SDL_Event event);
	void setX(int x);
	void setY(int y);
	void update(int offsetX,int offsetY, double delta = 0) override;
	void shoot(int mouseX, int mouseY);
	void setBulletsList(List* bullets);
};

