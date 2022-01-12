#include "Player.h"
#include <stdio.h>
#include <random>
#include <time.h>

Player::Player(Camera* camera,ColliderShape* shape, SDL_Surface* image):GameObject(shape, image) {
	this->speed = this->CONST_SPEED;
	this->camera = camera;
	srand(time(NULL));
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

bool Player::collision(GameObject* go,SDL_Surface* screen) {
	/*int width = 25;
	int height = 25;
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	
	Vector2 np = go->shape->nearestPoint(*this->x, *this->y);
	Graphics::Rectangle(screen, np.x-3, np.y-3,6,6,czerwony,czerwony);
		
	if (this->shape->collision(np.x, np.y)) {
		
	}*/
	return false;
}

void Player::setX(int x) {
	*this->x = x;
}

void Player::setY(int y) {
	*this->y = y;
}

void Player::horizontalMovement(double delta) {
	double x = this->direction.x;
	double y = this->direction.y;
	double v = sqrt(x * x + y * y);
	if (v > 0) {
		x = x / v;
		y = y / v;
	}

	x = this->speed * x * delta;
	*this->x += x;
	//this->camera->update(x, *this->y, this);
}

void Player::verticalMovement(double delta) {
	double x = this->direction.x;
	double y = this->direction.y;
	double v = sqrt(x * x + y * y);
	if (v > 0) {
		x = x / v;
		y = y / v;
	}
	/*printf("%d %d\n", *this->x, *this->y);*/
	y = this->speed * y * delta;

	*this->y += y;
	//this->camera->update(*this->x, y, this);
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