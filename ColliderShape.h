#pragma once
#include "Graphics.h"
#include "Vector2.h"

class ColliderShape{
protected:
	//center of the shape
	int x;
	int y;
	Uint32 color;
public:
	//checking if point is inside of a shape
	virtual bool collision(int x, int y) = 0;
	virtual Vector2 nearestPoint(int x, int y) = 0;
	virtual void setColliderPoint(int x, int y) = 0;
	virtual void draw(SDL_Surface* screen, int offsetX = 0, int offsetY = 0) = 0;

	//returns vector2 between center of the shape and given point
	Vector2 centerVector(int x, int y);
	int* getX();
	int* getY();
};