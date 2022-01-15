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
	virtual int getSize() = 0;
	virtual Vector2 getOffset() = 0;
	Vector2 wallCollision(int x, int y);
	//returns vector2 between center of the shape and given point
	Vector2 centerVector(int x, int y);
	void changeColor(Uint32 color);
	int* getX();
	int* getY();
	void addX(int x);
	void addY(int y);

	void setCoords(int x, int y);
};