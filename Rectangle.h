#pragma once
#include "ColliderShape.h"
class Rectangle: public ColliderShape{
private:
	int width;
	int height;
public:
	Rectangle(int x, int y, int width, int height, Uint32 color);

	//Override
	virtual bool collision(int* x, int* y);
	virtual void draw(SDL_Surface* screen);
	int getWidth();
	int getHeight();
};

