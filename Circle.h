#pragma once
#include "ColliderShape.h"
class Circle: public ColliderShape{
private:
	int radius;
	Uint32 borderColor = 0;
public:
	Circle(int x, int y, int radius, Uint32 color, Uint32 borderColor = 0);

	virtual bool collision(int x, int y) override;
	virtual Vector2 nearestPoint(int x, int y) override;
	virtual void setColliderPoint(int x, int y) override;
	virtual void draw(SDL_Surface* screen, int offsetX = 0, int offsetY = 0) override;
	virtual int getSize() override; //returning 
	virtual Vector2 getOffset() override;
};