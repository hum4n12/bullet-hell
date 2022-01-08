#include "Wall.h"

Wall::Wall(ColliderShape* shape, SDL_Surface* image) :GameObject(shape, image) {}


void Wall::update(int offsetX, int offsetY, double delta) {
	*this->x = offsetX;
	*this->y = offsetY;
}

void Wall::draw(SDL_Surface* screen,int offsetX, int offsetY){
	this->shape->draw(screen,offsetX,offsetY);
}
