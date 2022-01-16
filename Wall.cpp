#include "Wall.h"
#include <stdio.h>

Wall::Wall(ColliderShape* shape, SDL_Surface* image) :GameObject(shape, image) {}


void Wall::update(int offsetX, int offsetY, double delta) {
	*this->x = offsetX;
	*this->y = offsetY;
}

void Wall::draw(SDL_Surface* screen,int offsetX, int offsetY){
	if(MODE)
		Graphics::Rectangle(screen, *this->shape->getX() - offsetX, *this->shape->getY()-offsetY, this->shape->getSize(), this->shape->getSize(),Graphics::green, Graphics::green);
}

bool Wall::collision(GameObject* go) {
	Vector2 goNP = go->shape->wallCollision(*this->x, *this->y);//np = nearest point

	if (this->shape->collision(goNP.x, goNP.y)) {
		return true;
	}

	return false;
}