#pragma once
#include "GameObject.h"
#include "GLOBALS.h"
#include "Camera.h"
#include "Rectangle.h"
#include "List.h"
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define INVICIBLE_TIME 5

class Player :public GameObject{
private:
	Camera* camera;
	List* bullets;
	int const CONST_SPEED = 650;
	bool isInvicible = false;
	double invicibleTimer = 0;
public:
	Player(Camera* camera,ColliderShape* shape, SDL_Surface* image = nullptr);
	bool getInvicibility();
	void setInvicibility();
	void controls(SDL_Event event);
	void setX(int x);
	void setY(int y);
	void update(int offsetX,int offsetY, double delta = 0) override;
	void shoot(int mouseX, int mouseY);
	void setBulletsList(List* bullets);
};

