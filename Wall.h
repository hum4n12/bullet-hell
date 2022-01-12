#pragma once
#include "GameObject.h"
class Wall:public GameObject{
public:
	Wall(ColliderShape* shape, SDL_Surface* image = nullptr);
	void update(int offsetX,int offsetY, double delta = 0) override;
	void draw(SDL_Surface* screen, int offsetX = 0, int offsetY = 0) override;
	bool collision(GameObject* go, SDL_Surface* screen) override;
};