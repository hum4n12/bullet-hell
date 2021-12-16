#include "ColliderShape.h"

int* ColliderShape::getX() {
	return &this->x;
}

int* ColliderShape::getY() {
	return &this->y;
}