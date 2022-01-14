#pragma once
#include "SDL2-2.0.10/include/SDL.h"
#include "ColliderShape.h"
#include "Vector2.h"

class GameObject{
protected:
	int* x;
	int* y;
	int speed;
	Vector2 direction;
	SDL_Surface* image;
public:
	ColliderShape* shape;

	GameObject(ColliderShape* shape, SDL_Surface* image = nullptr);
	SDL_Surface* getImage();
	void addCoords(int x, int y);
	void setCoords(int x, int y);
	void setX(int x);
	void setY(int y);
	void addX(int x);
	void addY(int y);
	void setImage(SDL_Surface* image);
	Vector2 getDirection();

	void horizontalMovement(double delta);
	void verticalMovement(double delta);

	virtual void collisionReact(int x, int y);
	virtual void time(double delta);

	bool collision(GameObject* go);
	virtual void draw(SDL_Surface* screen, int offsetX = 0, int offsetY = 0);
	virtual void update(int offsetX, int offsetY,double delta = 0) = 0;
};