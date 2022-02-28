#include "Player.h"
#include "Bullet.h"
#include "Circle.h"
#include <stdio.h>
#include <string.h>
#define MAX_SCORE 999999999
#define MIN_SCORE 0
#define PLAYER_ANIMATIONS "./graphics/animations/player/"

Player::Player(Camera* camera,ColliderShape* shape, SDL_Surface* image):GameObject(shape, image) {
	this->speed = this->CONST_SPEED;
	this->camera = camera;
	this->hp = PLAYER_HP;
	strcat(this->runPath, PLAYER_ANIMATIONS"run.bmp");
	strcat(this->attackPath, PLAYER_ANIMATIONS"attack.bmp");
	strcat(this->idlePath, PLAYER_ANIMATIONS"idle.bmp");
}
bool Player::getInvicibility(){
	return this->isInvicible;
}
void Player::setInvicibility(){
	this->isInvicible = true;
}


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
	this->animationTimer += delta * ANIMATION_SPEED;
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (*this->x < mouseX) {
		this->flip = true;
	}
	else {
		this->flip = false;
	}

	//animations
	if (this->direction.x == 0 && this->direction.y == 0 && this->currAnimation != IDLE) {
		this->currAnimation = IDLE;
		this->animationTimer = 1;
	}
	else if ((this->direction.x != 0 || this->direction.y != 0 )&& this->currAnimation != RUN) {
		this->currAnimation = RUN;
		this->animationTimer = 1;
	}

	if (this->animationTimer >= this->animations->getSize(this->currAnimation)+1) {
		this->animationTimer = 1;
	}

	this->frame = (int)this->animationTimer;
	this->animationRect = this->animations->getFrame(this->currAnimation, this->frame);

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
	GameObject* bullet = new Bullet(Vector2{(double)mouseX,(double)mouseY}, 900, new Circle(*this->x, *this->y, 15, Graphics::white,Graphics::darkRed),nullptr,1);
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
	if (this->isInvicible && x > 0) {
		return;
	}
	this->updateScore(-1 * x);
	this->hp -= x;
	if (this->hp > PLAYER_HP) {
		this->hp += x;
	}
	this->isInvicible = true;
}

unsigned long Player::getScore() {
	return this->score;
}

void Player::draw(SDL_Surface* surface, int offsetX , int offsetY ) {
	if (this->isInvicible) {
		this->drawingInvicible++;
		if (drawingInvicible % 4 == 0) {
			return;
		}
	}
	else {
		this->drawingInvicible = 0;
	}
	
	if (this->image != nullptr) {
		if(this->flip) this->image = this->animations->getAnimationFlip(this->currAnimation);
		else this->image = this->animations->getAnimation(this->currAnimation);
		//this->shape->draw(surface, offsetX, offsetY);
		offsetX = this->animationRect->w / 2 + PLAYER_WIDTH / 4;
		offsetY = this->animationRect->h/2 - 2;
		Graphics::Surface(surface, this->image, *this->x - offsetX, *this->y - offsetY,this->animationRect,false);
		//Graphics::Surface(surface, this->image, *this->x - offsetX, *this->y - offsetY);
	}
	else {
		this->shape->draw(surface, offsetX, offsetY);
	}
}