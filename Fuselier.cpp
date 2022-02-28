#include "Fuselier.h"
#define FUSELIER_SPEED 0
#define FUSELIER_HEALTH 20
#define BULLET_DELAY 1.5
#include <stdlib.h>
#include "Circle.h"
#include "ExplosiveBullet.h"
#include <stdio.h>

Fuselier::Fuselier(Player* player, List* bullets, int x, int y) :Enemy(
	player,
	bullets,
	FUSELIER_SPEED,
	new Circle(x, y, 40, Graphics::cyan)
)
{
	this->animationOffset.x = 14;
	this->animationOffset.y = 80;
	this->hp = FUSELIER_HEALTH;
	this->timeToShoot = 2.0f;
}

void Fuselier::update(int offsetX, int offsetY, double delta) {
	this->delta = delta;

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
		this->animationTimer += delta * ANIMATION_SPEED / 2;
		if (this->animationTimer >= this->animations->getSize(this->currAnimation) + 1) {
			this->animationTimer = 1;
		}

		this->frame = (int)this->animationTimer;
		this->animationRect = this->animations->getFrame(this->currAnimation, this->frame);
	}



	if (this->bigBulletTimerFlag) {
		this->bigBulletTimer += this->delta;
	}


	if (this->bigBulletTimer >= BULLET_DELAY) {
		this->bigBulletTimerFlag = 0;
		//this->lastBullet->setSpeed(BULLET_SPEED+100);
		this->speed = FUSELIER_SPEED;
		this->bigBulletTimer = 0;
	}


	this->setDirection();
}

void Fuselier::shoot() {
	int attack = rand() % 2;
	if (attack == 0) {
		this->bigBulletAttack();
	}
	else{
		this->explosionAttack();
	}
}

void Fuselier::bigBulletAttack() {
	if (this->bigBulletTimer == 0) {
		this->bigBulletTimerFlag = 1;
		this->speed = 0;
		GameObject* bullet = new Bullet(this->player, BULLET_SPEED+100, new Circle(*this->x, *this->y, BULLET_SIZE*3, Graphics::red));
		this->bullets->push(bullet);
		this->lastBullet = bullet;
		bullet->update(0, 0, 0);
	}
}

void Fuselier::explosionAttack() {
	GameObject* bullet = new ExplosiveBullet(this->player,this->bullets,BULLET_SPEED, new Circle(*this->x, *this->y, BULLET_SIZE+5, Graphics::orange));
	this->bullets->push(bullet);
	bullet->update(0, 0, 0);
}