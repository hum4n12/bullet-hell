#pragma once
#include "GameObject.h"
#include "GLOBALS.h"
#include "Camera.h"
#include "Rectangle.h"
#include "List.h"
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define INVICIBLE_TIME 1

class Player :public GameObject{
private:
	Camera* camera;
	List* bullets;
	int const CONST_SPEED = 650;
	bool isInvicible = false;
	double invicibleTimer = 0;
	double attackDelay = 0.4;
	double attackDelayTimer = 0;
	
	unsigned long score = 0;
	int scoreBonus = 1;
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
	void updateScore(int x);
	void hit(int x = 1);
	unsigned long getScore();
};

