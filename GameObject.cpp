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

int GameObject::getHitValue()
{
	return this->hitValue;
}

void GameObject::initAnimations(SDL_Surface* run, SDL_Surface* attack, SDL_Surface* idle){
	this->animations = new Animations(run, attack, idle);
}

Vector2 GameObject::getDirection(){
	return this->direction;
}

bool GameObject::isDead()
{
	return (this->hp <= 0 );
}


bool GameObject::collision(GameObject* go){
	Vector2 goNP = go->shape->nearestPoint(*this->x, *this->y);//np = nearest point

	if (this->shape->collision(goNP.x, goNP.y)) {
		return true;
	}

	return false;
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

void GameObject::setSpeed(int speed){
	this->speed = speed;
}

void GameObject::draw(SDL_Surface* surface, int offsetX, int offsetY) {
	
	if (this->image != nullptr) {
		Graphics::Surface(surface, this->image, *this->x - offsetX, *this->y - offsetY);
	}
	else {
		this->shape->draw(surface,offsetX,offsetY);
	}
}

void GameObject::horizontalMovement(double delta) {
	double x = this->direction.x;
	double y = this->direction.y;
	double v = sqrt(x * x + y * y);
	if (v > 0) {
		x = x / v;
		y = y / v;
	}

	x = this->speed * x * delta;
	*this->x += x;
}

void GameObject::verticalMovement(double delta) {
	double x = this->direction.x;
	double y = this->direction.y;
	double v = sqrt(x * x + y * y);
	if (v > 0) {
		x = x / v;
		y = y / v;
	}
	y = this->speed * y * delta;

	*this->y += y;
}

void GameObject::collisionReact(int x, int y)
{
}

void GameObject::time(double delta) {

}
