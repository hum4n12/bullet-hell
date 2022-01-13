#include "Wall.h"
#include <stdio.h>

Wall::Wall(ColliderShape* shape, SDL_Surface* image) :GameObject(shape, image) {}


void Wall::update(int offsetX, int offsetY, double delta) {
	*this->x = offsetX;
	*this->y = offsetY;
}

void Wall::draw(SDL_Surface* screen,int offsetX, int offsetY){
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);

	Graphics::Rectangle(screen, *this->shape->getX() - offsetX, *this->shape->getY()-offsetY, this->shape->getSize(), this->shape->getSize(),zielony,zielony);
	//this->shape->draw(screen,offsetX,offsetY);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	Graphics::Pixel(screen, *this->x, *this->y, czerwony);
}
