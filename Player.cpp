#include "Player.h"
#include <stdio.h>

Player::Player(Camera* camera,ColliderShape* shape, SDL_Surface* image):GameObject(shape, image) {
	this->speed = 700;
	this->camera = camera;
};

void Player::controls(SDL_Event event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case(SDLK_RIGHT):
				this->direction.x = 1;
				break;
		case(SDLK_LEFT):
				this->direction.x = -1;
				break;
		case(SDLK_UP):
				this->direction.y = -1;
				break;
		case(SDLK_DOWN):
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
		case(SDLK_LEFT):
			if (this->direction.x < 0)
				this->direction.x = 0;
			break;
		case(SDLK_UP):
			if (this->direction.y < 0)
				this->direction.y = 0;
			break;
		case(SDLK_DOWN):
			if (this->direction.y > 0)
				this->direction.y = 0;
			break;
		}
		break;
	};
}

bool Player::collision(GameObject* go) {
	//left-upper corner
	int rc = *this->x + this->shape
	if (go->shape->collision(this->x) && (go->shape->collision(this->x)) {

	}


}

void Player::addCoords(int x, int y) {
	*this->x += x;
	*this->y += y;
}

void Player::update(double delta,int offsetX,int offsetY) {
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

	this->camera->update(x, y,this);
	printf("\n%d %d", this->camera->originX, this->camera->originY);
}