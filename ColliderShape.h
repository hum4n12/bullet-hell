#pragma once
#include "Graphics.h"

class ColliderShape{
protected:
	int x;
	int y;
	Uint32 color;
public:
	virtual bool collision(int* x = nullptr, int* y = nullptr) = 0;
	virtual void draw(SDL_Surface* screen) = 0;
	int* getX();
	int* getY();
};

