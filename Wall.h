#pragma once
#include "GameObject.h"
class Wall:public GameObject{
public:
	Wall(ColliderShape* shape, SDL_Surface* image = nullptr);
	void update(double delta,int offsetX,int offsetY) override;
	void draw(SDL_Surface* screen) override;
};