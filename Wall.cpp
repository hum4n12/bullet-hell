#include "Wall.h"
#include <stdio.h>

Wall::Wall(ColliderShape* shape, SDL_Surface* image) :GameObject(shape, image) {}


void Wall::update(int offsetX, int offsetY, double delta) {
	*this->x = offsetX;
	*this->y = offsetY;
}

void Wall::draw(SDL_Surface* screen,int offsetX, int offsetY){
	this->shape->draw(screen,offsetX,offsetY);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	Graphics::Pixel(screen, *this->x, *this->y, czerwony);
}

bool Wall::collision(GameObject* go, SDL_Surface* screen){
	Vector2 goNP = go->shape->nearestPoint(*this->x, *this->y);//np = nearest point

	if (this->shape->collision(goNP.x, goNP.y)) {
		Vector2 dir = go->getDirection();
		printf("%d %d \n", dir.x, dir.y);
	}
}
