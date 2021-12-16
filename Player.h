#pragma once
#include "GameObject.h"
#include "GLOBALS.h"
#include "Camera.h"
#include "Rectangle.h"

class Player :public GameObject{
private:
	Camera* camera;
	Rectangle* shape;
public:
	Player(Camera* camera,ColliderShape* shape, SDL_Surface* image = nullptr);
	bool collision(GameObject* go);
	void controls(SDL_Event event);
	void addCoords(int x, int y);
	void update(double delta, int offsetX,int offsetY) override;
};

