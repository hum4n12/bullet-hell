#include "Player.h"
#include "Bullet.h"
#include "Circle.h"
#include <stdio.h>
#define MAX_SCORE 999999999
#define MIN_SCORE 0

Player::Player(Camera* camera,ColliderShape* shape, SDL_Surface* image):GameObject(shape, image) {
	this->speed = this->CONST_SPEED;
	this->camera = camera;
	this->hp = PLAYER_HP-2;
}
bool Player::getInvicibility(){
	return this->isInvicible;
}
void Player::setInvicibility(){
	this->isInvicible = true;
}
;

void Player::controls(SDL_Event event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case(SDLK_RIGHT):
			this->direction.x = 1;
			break;
		
		case(SDLK_d):
			this->direction.x = 1;
			break;

		case(SDLK_LEFT):
			this->direction.x = -1;
			break;

		case(SDLK_a):
			this->direction.x = -1;
			break;

		case(SDLK_UP):
			this->direction.y = -1;
			break;

		case(SDLK_w):
			this->direction.y = -1;
			break;

		case(SDLK_DOWN):
			this->direction.y = 1;
			break;

		case(SDLK_s):
			this->direction.y = 1;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case(SDLK_RIGHT):
			if (this->direction.x > 0)
				this->direction.x = 0;
			break;
		
		case(SDLK_d):
			if (this->direction.x > 0)
				this->direction.x = 0;
			break;

		case(SDLK_LEFT):
			if (this->direction.x < 0)
				this->direction.x = 0;
			break;

		case(SDLK_a):
			if (this->direction.x < 0)
				this->direction.x = 0;
			break;

		case(SDLK_UP):
			if (this->direction.y < 0)
				this->direction.y = 0;
			break;
		
		case(SDLK_w):
			if (this->direction.y < 0)
				this->direction.y = 0;
			break;

		case(SDLK_DOWN):
			if (this->direction.y > 0)
				this->direction.y = 0;
			break;
		
		case(SDLK_s):
			if (this->direction.y > 0)
				this->direction.y = 0;
			break;
		}
		break;
	case (SDL_MOUSEBUTTONDOWN):
		int mouseX = 0;
		int mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);
		if (this->attackDelayTimer >= this->attackDelay) {
			this->shoot(mouseX, mouseY);
			this->attackDelayTimer = 0;
		}
		break;
	}
}

void Player::setX(int x) {
	*this->x = x;
}

void Player::setY(int y) {
	*this->y = y;
}

void Player::update(int offsetX,int offsetY, double delta) {
	if (this->isInvicible) {
		this->invicibleTimer += delta;
	}
	if (this->invicibleTimer >= INVICIBLE_TIME) {
		this->invicibleTimer = 0;
		this->isInvicible = false;
	}
	this->attackDelayTimer += delta;
}

void Player::shoot(int mouseX, int mouseY){
	GameObject* bullet = new Bullet(Vector2{(double)mouseX,(double)mouseY}, 900, new Circle(*this->x, *this->y, 15, Graphics::white),nullptr,1);
	this->bullets->push(bullet);
	bullet->update(0, 0, 0); //updating direction
}

void Player::setBulletsList(List* bullets) {
	this->bullets = bullets;
}

void Player::updateScore(int x){
	if (x < 0) {
		this->scoreBonus = 1;
		this->score -= this->score * 0.2;
		if (this->score < MIN_SCORE)
			this->score = MIN_SCORE;
	}
	else {
		if (this->score < MAX_SCORE) {
			if (this->score == MIN_SCORE) {
				this->score = 1;
			}
			else {
				this->score += scoreBonus;
			}
			this->scoreBonus+=1;
		}
		else {
			this->score = MAX_SCORE;
		}
	}
}

void Player::hit(int x){
	if (this->isInvicible) {
		return;
	}
	this->updateScore(-1 * x);
	this->hp -= x;
	this->isInvicible = true;
}

unsigned long Player::getScore() {
	return this->score;
}