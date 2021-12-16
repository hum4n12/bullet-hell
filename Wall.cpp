#include "Wall.h"

Wall::Wall(ColliderShape* shape, SDL_Surface* image) :GameObject(shape, image) {}


void Wall::update(double delta, int offsetX, int offsetY) {
	*this->x -= offsetX;
	*this->y -= offsetY;
}

void Wall::draw(SDL_Surface* screen)
{
	return;
}
