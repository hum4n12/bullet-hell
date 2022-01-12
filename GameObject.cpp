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

Vector2 GameObject::getDirection(){
	return this->direction;
}


SDL_Surface* GameObject::getImage() {
	return this->image;
}

void GameObject::addCoords(int x, int y) {
	*this->x += x;
	*this->y += y;
}

void GameObject::setCoords(int x, int y) {
	*this->x = x;
	*this->y = y;
}

void GameObject::setX(int x){
	*this->x = x;
}

void GameObject::setY(int y) {
	*this->y = y;
}

void GameObject::addX(int x) {
	*this->x += x;
}

void GameObject::addY(int y) {
	*this->y += y;
}

void GameObject::draw(SDL_Surface* surface, int offsetX, int offsetY) {
	
	if (this->image != nullptr) {
		Graphics::Surface(surface, this->image, *this->x - offsetX, *this->y - offsetY);
	}
	else {
		this->shape->draw(surface,offsetX,offsetY);
	}
}