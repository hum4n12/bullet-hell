#include "Camera.h"
#include <stdio.h>
#include "Level.h"

Camera::Camera(Player* player) {
	this->player = player;
	this->originX = *player->shape->getX() - PLAYER_WIDTH/2;
	this->originY = *player->shape->getY()- PLAYER_HEIGHT/2;
	this->left = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
	this->top = SCREEN_HEIGHT / 2 - PLAYER_HEIGHT / 2;
}

void Camera::setLevelDimensions(int levelWidth, int levelHeight) {
	this->right = levelWidth - SCREEN_WIDTH / 2 - TILE_SIZE/2;
	this->bottom = levelHeight - SCREEN_HEIGHT / 2 - TILE_SIZE / 2;
}

void Camera::update() {
	this->x = (*this->player->shape->getX() + PLAYER_WIDTH/2) - SCREEN_WIDTH / 2;
	this->y = (*this->player->shape->getY() + PLAYER_HEIGHT/2) - SCREEN_HEIGHT / 2;

	this->originX += this->x;
	this->originY += this->y;


	if (this->offsetX != 0) {
		//if there was an offset, it means that camera is not moving
		this->offsetX = 0;
		this->originX -= this->x;
		this->x = 0;
	}
	
	if (this->offsetY != 0) {
		this->offsetY = 0;
		this->originY -= this->y;
		this->y = 0;
	}

	if (this->originX <= this->left) {

		//after moving a player, calculate offset the rest of the objects
		this->originX -= this->x;
		this->offsetX = this->left - this->originX;

		this->originX = this->left;
		
		this->x = this->offsetX;
	}

	if (this->originY <= this->top) {
		this->originY -= this->y;
		this->offsetY = this->top - this->originY;

		this->originY = this->top;

		this->y = this->offsetY;
	}

	if (this->originX > this->right) {
		this->originX -= this->x;
		this->offsetX = this->right - this->originX;

		this->originX = this->right;

		this->x = this->offsetX;
	}

	if (this->originY > this->bottom) {
		this->originY -= this->y;
		this->offsetY = this->bottom - this->originY;

		this->originY = this->bottom;

		this->y = this->offsetY;
	}
}

//void Camera::update(int x, int y,Player* player, bool setX, bool setY) {
//	int offsetX = SCREEN_WIDTH / 2;
//	int offsetY = SCREEN_HEIGHT / 2;
//
//	if (setX) this->originX = x;
//	else this->originX += x;
//	
//	if (setY) this->originY = y;
//	else this->originY += y;
//	//player->addCoords(x, y);
//
//	printf("\n%d %d", this->x, this->y);
//	printf("\norigin: %d %d", this->originX, this->originY);
//
//	if (this->originX <= offsetX || this->originX >= this->levelWidth-offsetX || this->originY <= offsetY || this->originY >= this->levelHeight - offsetY) {
//		if (this->originX <= offsetX) {
//			this->x = 0; //it is offsetX - offsetX
//
//			if (setX) player->setX(x);
//			else player->addCoords(x, 0);
//		}
//		else if(this->originX >= this->levelWidth - offsetX){
//			this->x = this->levelWidth - offsetX*2;
//			
//			if (setX) player->setX(x);
//			else player->addCoords(x, 0);
//		}
//		else {
//			if (setX) this->x = offsetX - 25;
//			else this->x += x;
//			player->setX(offsetX);
//		}
//		if (this->originY <= offsetY) {
//			this->y = 0;
//			player->addCoords(0, y);
//		}
//		else if(this->originY >= this->levelHeight - offsetY) {
//			this->y = this->levelHeight - offsetY * 2;
//			player->addCoords(0, y);
//		}
//		else {
//			this->y += y;
//			player->setY(offsetY);
//		}
//	}
//	else {
//		if (setX) this->x = originX-25;
//		else this->x += x;
//		this->y += y;
//
//		player->setX(offsetX);
//		player->setY(offsetY);
//	}
//}