#include "GameObject.h"
#include "AnimationsList.h"
#include <stdio.h>
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

void GameObject::initAnimations(Animations* a){
	if (a == nullptr) {
		SDL_Surface* run;
		SDL_Surface* attack = nullptr;
		SDL_Surface* idle = nullptr;

		//run = Graphics::loadImage("./graphics/animations/player/run.bmp");
		run = Graphics::loadImage(this->runPath);
		attack = Graphics::loadImage(this->attackPath);
		idle = Graphics::loadImage(this->idlePath);
		this->animations = new Animations(run, attack, idle);
	}
	else {
		this->animations = a;
	}
	this->animationRect = this->animations->getFrame(RUN, this->frame);
	this->image = this->animations->getAnimation(RUN);
	this->currAnimation = RUN;
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
		if(MODE)
			this->shape->draw(surface, offsetX, offsetY);
		if (this->animations != nullptr) {
			if (this->flip) {
				this->image = this->animations->getAnimationFlip(this->currAnimation);
			}
			else {
				this->image = this->animations->getAnimation(this->currAnimation);
			}
			offsetX = this->animationRect->w / 2 - this->animationOffset.x * this->direction.x;
			offsetY = this->animationOffset.y;
			Graphics::Surface(surface, this->image, *this->x - offsetX, *this->y - offsetY, this->animationRect, false);
		}
		else {
			/*offsetX = 64;
			offsetY = 64;*/
		}
		Graphics::Surface(surface, this->image, *this->x - offsetX, *this->y - offsetY, this->animationRect, false);
	}
	else {
		this->shape->draw(surface,offsetX,offsetY);
	}

	if (this->drawingHit > 0) {
		Graphics::drawHit(surface, *this->x, *this->y, this->shape->getSize()*0.7);
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

void GameObject::collisionReact(int x, int y){
}

void GameObject::time(double delta) {

}
