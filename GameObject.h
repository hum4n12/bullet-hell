#pragma once
#include "SDL2-2.0.10/include/SDL.h"
#include "ColliderShape.h"
#include "Vector2.h"

class GameObject{
protected:
	int* x;
	int* y;
	double speed;
	Vector2 direction;
	SDL_Surface* image;
public:
	ColliderShape* shape;
	GameObject(ColliderShape* shape, SDL_Surface* image = nullptr);
	SDL_Surface* getImage();
	void setImage(SDL_Surface* image);
	virtual void draw(SDL_Surface* screen);
	virtual void update(double delta,int offsetX, int offsetY) = 0;
};