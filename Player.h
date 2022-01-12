#pragma once
#include "GameObject.h"
#include "GLOBALS.h"
#include "Camera.h"
#include "Rectangle.h"

class Player :public GameObject{
private:
	Camera* camera;
	int const CONST_SPEED = 700;
public:
	Player(Camera* camera,ColliderShape* shape, SDL_Surface* image = nullptr);
	bool collision(GameObject* go,SDL_Surface* screen) override;
	void controls(SDL_Event event);
	void setX(int x);
	void setY(int y);
	void horizontalMovement(double delta);
	void verticalMovement(double delta);
	void update(int offsetX,int offsetY, double delta = 0) override;
};

