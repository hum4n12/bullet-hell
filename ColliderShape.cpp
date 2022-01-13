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

Vector2 ColliderShape::centerVector(int x, int y) {
	Vector2 v;
	
	//if v.x < 0 , the given point is on the left. v.y < 0 -> given point is on the top
	v.x = x - this->x;
	v.y = y - this->y;

	return v;
}