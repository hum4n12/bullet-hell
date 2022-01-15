#include "Player.h"
#include "Bullet.h"
#include "Circle.h"
#include <stdio.h>

Player::Player(Camera* camera,ColliderShape* shape, SDL_Surface* image):GameObject(shape, image) {
	this->speed = this->CONST_SPEED;
	this->camera = camera;
};

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
		printf("\n%d", mouseX);
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
	/*printf("\n %d %d", *this->x, *this->y);*/
	//normalizing vectors
	double x = this->direction.x;
	double y = this->direction.y;
	double v = sqrt(x * x + y * y);
	if (v > 0) { 
		x = x / v;
		y = y / v;
	}
	x = this->speed * x * delta;
	y = this->speed * y * delta;

	// move x,check if

	//this->camera->update(x, y,this);
	//printf("\n%d %d", this->camera->originX, this->camera->originY);
}

void Player::shoot(int mouseX, int mouseY){
	GameObject* bullet = new Bullet(Vector2{(double)mouseX,(double)mouseY}, 900, new Circle(*this->x, *this->y, 15, Graphics::white),nullptr,1);
	this->bullets->push(bullet);
	bullet->update(0, 0, 0); //updating direction
}

void Player::setBulletsList(List* bullets) {
	this->bullets = bullets;
}