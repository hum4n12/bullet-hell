#include "Knight.h"
#include <stdio.h>
#include <stdlib.h>
#define KNIGHT_SPEED 600
#define KNIGHT_HEALTH 40
#define ATTACK_DELAY 2.0
#define ATTACK_DISTANCE 150
#include "Zone.h"
#define ZONE_SIZE 128
#define KNIGHT_WIDTH 70
#define KNIGHT_HEIGHT 110

Knight::Knight(Player* player, List* bullets, int x, int y) :Enemy(
	player,
	bullets,
	KNIGHT_SPEED,
	new Rectangle(x, y, KNIGHT_WIDTH, KNIGHT_HEIGHT, Graphics::cyan)
)
{
	this->attackZone = Graphics::loadImage("./graphics/attack_zone.bmp");
	this->warningZone = Graphics::loadImage("./graphics/warning_zone.bmp");
	this->animationOffset.x = 20;
	this->animationOffset.y = 80;
	this->hp = KNIGHT_HEALTH;
	this->timeToShoot = 0.0f;
}

void Knight::update(int offsetX, int offsetY, double delta) {
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

	if (this->attackDelayFlag) {
		this->attackDelayTimer += this->delta;
	}


	if (this->attackDelayTimer >= ATTACK_DELAY) {
		this->attackDelayFlag = 0;
		/*this->lastBullet->setSpeed(300);*/
		this->speed = KNIGHT_SPEED;
		this->attackDelayTimer = 0;
	}

	this->setDirection();

	for (int i = 0; i < this->zones.getSize(); i++) {
		GameObject* go = this->zones.get(i);
		go->addCoords(-offsetX, -offsetY);
		go->update(0,0,delta);

		if (go->customFlag && go->collision(this->player)) {
			this->player->hit();
		}
	}

	for (int i = this->zones.getSize() - 1; i >= 0; i--) {
		GameObject* go = this->zones.get(i);
		if (go->customFlag) {
			this->zones.remove(i);
		}
	}
}

void Knight::draw(SDL_Surface* surface, int offsetX, int offsetY) {
	for (int i = 0; i < this->zones.getSize(); i++) {
		GameObject* go = this->zones.get(i);
		go->draw(surface, ZONE_SIZE / 2, ZONE_SIZE / 2);
	}

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
		}
		else {
			offsetX = this->animationRect->w / 2 + 20;
		}
		offsetY = this->animationOffset.y;
		Graphics::Surface(surface, this->image, *this->x - offsetX, *this->y - offsetY, this->animationRect, false);
	}
	else {
		this->shape->draw(surface, offsetX, offsetY);
	}
	
	if (this->drawingHit > 0) {
		Graphics::drawHit(surface, *this->x, *this->y, this->shape->getSize() * 0.7);
	}
}

void Knight::shoot() {
	double distance = sqrt(pow((*this->x - *this->player->shape->getX()),2)+pow((*this->y - *this->player->shape->getY()),2));
	
	int attack = rand() % 2;
	if (distance <= ATTACK_DISTANCE) {
		if (attack == 0)
			this->verticalAttack();
		else
			this->horizontalAttack();
	}
}

void Knight::horizontalAttack() {
	if (this->attackDelayTimer == 0) {
		this->attackDelayFlag = 1;
		this->speed = 0;
	
		GameObject* one = new Zone(new Rectangle(*this->x-25 + this->direction.x*100, *this->y-25 + this->direction.y*100, ZONE_SIZE, ZONE_SIZE, Graphics::blue),this->warningZone,this->attackZone);
		this->zones.push(one);
		
		//cos(this->atan2Angle - M_PI / 180 * 45);
		one = new Zone(new Rectangle(*this->x - 25 + cos(this->atan2Angle - M_PI / 180 * 45) * 100, *this->y - 25 + sin(this->atan2Angle - M_PI / 180 * 45) * 100, ZONE_SIZE, ZONE_SIZE, Graphics::blue), this->warningZone, this->attackZone);
		this->zones.push(one);
		
		one = new Zone(new Rectangle(*this->x - 25 + cos(this->atan2Angle + M_PI / 180 * 45) * 100, *this->y - 25 + sin(this->atan2Angle + M_PI / 180 * 45) * 100, ZONE_SIZE, ZONE_SIZE, Graphics::blue), this->warningZone, this->attackZone);
		this->zones.push(one);
	}
}

void Knight::verticalAttack() {
	if (this->attackDelayTimer == 0) {
		this->attackDelayFlag = 1;
		this->speed = 0;
		Vector2 center{ *this->x - 25, *this->y - 25 };
		double offset = 40;

		GameObject* one = new Zone(new Rectangle(center.x + this->direction.x * 100, center.y + this->direction.y * 100, ZONE_SIZE, ZONE_SIZE, Graphics::blue), this->warningZone, this->attackZone);
		this->zones.push(one);

		center.x += this->direction.x * offset;
		center.y += this->direction.y * offset;
		
		one = new Zone(new Rectangle(center.x + this->direction.x * 100, center.y + this->direction.y * 100, ZONE_SIZE, ZONE_SIZE, Graphics::blue), this->warningZone, this->attackZone);
		this->zones.push(one);

		center.x += this->direction.x * offset;
		center.y += this->direction.y * offset;

		one = new Zone(new Rectangle(center.x + this->direction.x * 100, center.y + this->direction.y * 100, ZONE_SIZE, ZONE_SIZE, Graphics::blue), this->warningZone, this->attackZone);
		this->zones.push(one);
	}
}