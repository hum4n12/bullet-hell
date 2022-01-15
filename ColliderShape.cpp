#include "ColliderShape.h"

int* ColliderShape::getX() {
	return &this->x;
}

int* ColliderShape::getY() {
	return &this->y;
}

void ColliderShape::addX(int x){
	this->x += x;
}

void ColliderShape::addY(int Y) {
	this->y += y;
}

void ColliderShape::setCoords(int x, int y){
	this->x = x;
	this->y = y;
}

Vector2 ColliderShape::wallCollision(int x, int y){
	Vector2 pos;
	Vector2 offset = this->getOffset();
	int hw = (int)offset.x;
	int hh = (int)offset.y;
	pos.x = x - this->x;
	pos.y = y - this->y;

	if (pos.x > hw) pos.x = hw;
	else if (pos.x < -hw) pos.x = -hw;

	if (pos.y > hh) pos.y = hh;
	else if (pos.y < -hh) pos.y = -hh;
	//if point is inside of the rectangle

	pos.x += this->x;
	pos.y += this->y;

	return pos;
}

Vector2 ColliderShape::centerVector(int x, int y) {
	Vector2 v;
	
	//if v.x < 0 , the given point is on the left. v.y < 0 -> given point is on the top
	v.x = x - this->x;
	v.y = y - this->y;

	return v;
}

void ColliderShape::changeColor(Uint32 color) {
	this->color = color;
}