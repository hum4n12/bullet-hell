#include "Bullet.h"
#include <stdio.h>
Bullet::Bullet(Player* player, int speed, ColliderShape* shape, SDL_Surface* image) :GameObject(shape, image) {
	this->player = player;
	this->speed = speed;
}

Bullet::Bullet(Vector2 dir, int speed, ColliderShape* shape, SDL_Surface* image,bool playerBullet): GameObject(shape,image){
	this->speed = speed;
	this->directionSetter = dir;
	this->customFlag = playerBullet;
}

Bullet::Bullet(Vector2 dir,double angleOffset, int speed, ColliderShape* shape, SDL_Surface* image): GameObject(shape,image){
	this->speed = speed;
	this->directionSetter = dir;
	this->angleOffset = angleOffset;
}

void Bullet::setDirection(double radiusOffset) {
	double angle = 0;
	int pX = 0;
	int pY = 0;
	double q = 0;
	if (this->player != nullptr) {
		Vector2 playerOffset = this->player->shape->getOffset();
		pX = *this->player->shape->getX();
		pY = *this->player->shape->getY();
	}
	else {
		pX = (int)this->directionSetter.x;
		pY = (int)this->directionSetter.y;
		q = this->angleOffset;
		//q = M_PI;
	}
	
	int x = *this->shape->getX();
	int y = *this->shape->getY();
	angle = atan2(pY - y, pX - x) + q;
	angle += (double)radiusOffset;

	Vector2 dir = { cos(angle),sin(angle) };
	this->direction = dir;
}

void Bullet::update(int offsetX, int offsetY, double radiusOffset) {
	this->setDirection(radiusOffset);
}

Bullet::~Bullet(){
	printf("destroyed");
}

void Bullet::collisionReact(int x, int y)
{
}
