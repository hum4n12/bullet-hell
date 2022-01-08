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

void Player::collision(GameObject* go,SDL_Surface* screen) {
	int width = 25;
	int height = 25;
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	
	Vector2 np = go->shape->nearestPoint(*this->x, *this->y);
	Graphics::Rectangle(screen, np.x-3, np.y-3,6,6,czerwony,czerwony);
		
	if (this->shape->collision(np.x,np.y)) {
		this->speed = 10;
		//go->shape->setLastNP(np.x, np.y);
		Vector2 location = go->shape->centerVector(np.x, np.y);

		int xAxis = abs(location.x);
		int yAxis = abs(location.y);
		printf("\n%d %d %d", xAxis, yAxis, this->speed);
		//collision is on the left/right
		if (xAxis > yAxis) {
			if(location.x > 0)
				*this->x = np.x + width;
			else
				*this->x = np.x - width;
		}
		else if(xAxis < yAxis){
			if(location.y > 0)
				*this->y = np.y + height;
			else
				*this->y = np.y - height;
		}
		else{
			printf("\n %d %d \n", this->direction.x, this->direction.y);
			if (this->direction.y == 0) {
				*this->x = np.x - this->direction.x * (width+1);
			}
			else if (this->direction.x == 0) {
				*this->y = np.y - this->direction.y * (height+1);
			}
		}

		//this->shape->setColliderPoint(location.x, location.y);
	}
	else {
		//changing speed of player
		this->speed = this->CONST_SPEED;
		if (go->shape->lastNearestPoint != nullptr) {
			delete go->shape->lastNearestPoint;
			go->shape->lastNearestPoint = nullptr;
		}
	}
	//if (this->shape->collision(np.x, np.y)) {
	//	//printf("\n\n%d %d %d", np.x,np.y,rand()%100);
	//	this->shape->setColliderPoint(-1, np.y);
	//}
}

void Player::addCoords(int x, int y) {
	*this->x += x;
	*this->y += y;
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

	this->camera->update(x, y,this);
	//printf("\n%d %d", this->camera->originX, this->camera->originY);
}