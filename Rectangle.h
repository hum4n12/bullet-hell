#pragma once
#include "ColliderShape.h"
class Rectangle: public ColliderShape{
private:
	int width;
	int height;
public:
	Rectangle(int x, int y, int width, int height, Uint32 color);
	//Override
	virtual bool collision(int x, int y) override;
	virtual Vector2 nearestPoint(int x, int y) override;
	virtual void setColliderPoint(int x, int y) override;
	virtual void draw(SDL_Surface* screen, int offsetX = 0, int offsetY = 0) override;
};

