#include "Player.h"
#include "Bullet.h"
#include "Circle.h"
#include <stdio.h>

Player::Player(Camera* camera,ColliderShape* shape, SDL_Surface* image):GameObject(shape, image) {
	this->speed = this->CONST_SPEED;
	this->camera = camera;
	this->hp = PLAYER_HP;
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
		this->shoot(mouseX, mouseY);
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
}

void Player::shoot(int mouseX, int mouseY){
	GameObject* bullet = new Bullet(Vector2{(double)mouseX,(double)mouseY}, 900, new Circle(*this->x, *this->y, 15, Graphics::white),nullptr,1);
	this->bullets->push(bullet);
	bullet->update(0, 0, 0); //updating direction
}

void Player::setBulletsList(List* bullets) {
	this->bullets = bullets;
}