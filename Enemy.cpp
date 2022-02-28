#include "Enemy.h"
#include "stdio.h"
#include "Circle.h"

Enemy::Enemy(Player* player,List* bullets,int speed,ColliderShape* shape, SDL_Surface* image) :GameObject(shape, image) {
	this->player = player;
	this->speed = speed;
	this->bullets = bullets;
};

void Enemy::setDirection() {
	double angle = atan2(*this->player->shape->getY() - *this->shape->getY(), *this->player->shape->getX() - *this->shape->getX());
	this->atan2Angle = angle;


	Vector2 dir = { cos(angle),sin(angle) };
	this->direction = dir;
}

void Enemy::update(int offsetX, int offsetY, double delta){
	this->delta = delta;
	this->setDirection();

	if (this->drawingHit > 0) {
		this->drawingHit -= delta;
	}
	
	if (*this->x < *this->player->shape->getX()) {
		this->flip = true;
	}
	else {
		this->flip = false;
	}

	if (this->animations != nullptr) {
		this->animationTimer += delta * ANIMATION_SPEED/2;
		if (this->animationTimer >= this->animations->getSize(this->currAnimation) + 1) {
			this->animationTimer = 1;
		}

		this->frame = (int)this->animationTimer;
		this->animationRect = this->animations->getFrame(this->currAnimation, this->frame);
	}
}

void Enemy::time(double delta) {
	this->timer += delta;
	if (this->timer >= this->timeToShoot) {
		this->shoot();
		this->timer = 0;
	}
}

//void Enemy::shoot() {
//	GameObject* bullet = new Bullet(this->player,300,new Circle(*this->x ,*this->y,20,Graphics::red));
//	this->bullets->push(bullet);
//	bullet->update(0,0,0); //updating direction
//}
