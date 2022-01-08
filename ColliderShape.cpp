#include "ColliderShape.h"

int* ColliderShape::getX() {
	return &this->x;
}

int* ColliderShape::getY() {
	return &this->y;
}

Vector2 ColliderShape::centerVector(int x, int y) {
	Vector2 v;
	
	//if v.x < 0 , the given point is on the left. v.y < 0 -> given point is on the top
	v.x = x - this->x;
	v.y = y - this->y;

	return v;
}

void ColliderShape::setLastNP(int x, int y) {
	if (this->lastNearestPoint == nullptr) {
		this->lastNearestPoint = new Vector2{ x,y };
	}
}