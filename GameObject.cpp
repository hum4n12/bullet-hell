#include "GameObject.h"

GameObject::GameObject(ColliderShape* shape, SDL_Surface* image) {
	this->x = shape->getX();
	this->y = shape->getY();
	this->shape = shape;
	this->image = nullptr;
	this->speed = 0;
}

void GameObject::setImage(SDL_Surface* image) {
	this->image = image;
}


SDL_Surface* GameObject::getImage() {
	return this->image;
}

void GameObject::draw(SDL_Surface* surface, int offsetX, int offsetY) {
	
	if (this->image != nullptr) {
		Graphics::Surface(surface, this->image, *this->x - offsetX, *this->y - offsetY);
	}
	else {
		this->shape->draw(surface,offsetX,offsetY);
	}
}