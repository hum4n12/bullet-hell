#include "Camera.h"

void Camera::update(int x, int y,Player* player) {
	this->originX += x;
	this->originY += y;
	int offsetX = SCREEN_WIDTH / 2;
	int offsetY = SCREEN_HEIGHT / 2;
	player->addCoords(x, y);

	//if (this->originX <= offsetX || this->originX >= this->levelWidth-offsetX || this->originY <= offsetY || this->originY >= this->levelHeight - offsetY) {
	//	if (this->originX <= offsetX) {
	//		this->x = 0; //it is offsetX - offsetX
	//		player->addCoords(x, 0);
	//	}
	//	else if(this->originX >= this->levelWidth - offsetX){
	//		this->x = this->levelWidth - offsetX*2;
	//		player->addCoords(x, 0);
	//	}
	//	else {
	//		this->x += x;
	//		player->setX(offsetX);
	//	}
	//	if (this->originY <= offsetY) {
	//		this->y = 0;
	//		player->addCoords(0, y);
	//	}
	//	else if(this->originY >= this->levelHeight - offsetY) {
	//		this->y = this->levelHeight - offsetY * 2;
	//		player->addCoords(0, y);
	//	}
	//	else {
	//		this->y += y;
	//		player->setY(offsetY);
	//	}
	//}
	//else {
	//	this->x += x;
	//	this->y += y;
	//	player->setX(offsetX);
	//	player->setY(offsetY);
	//}
}