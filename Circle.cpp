#include "Circle.h"

Circle::Circle(int x, int y, int radius, Uint32 color,Uint32 borderColor) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->color = color;
	this->borderColor = borderColor;
}

bool Circle::collision(int x, int y) {
	return pow((x - this->x), 2) + pow(y - this->y, 2) <= pow(this->radius,2);
}

Vector2 Circle::nearestPoint(int x, int y) {
	Vector2 pos;
	pos.x = x - this->x;
	pos.y = y - this->y;
	
	double distance = sqrt((pos.x * pos.x) + (pos.y*pos.y));

	if (distance < this->radius) {
		pos.x = x;
		pos.y = y;
	}
	else {
		pos.x = pos.x / distance * this->radius + this->x;
		pos.y = pos.y / distance * this->radius + this->y;
	}
	
	return pos;
}

void Circle::setColliderPoint(int x, int y) {
	if (x >= 0)
		this->x = x;
	if (y >= 0)
		this->y = y;
}

void Circle::draw(SDL_Surface* screen, int offsetX, int offsetY) {
	if(this->color == 0)
		this->color = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	Graphics::Circle(screen, this->x, this->y, this->radius,this->color,this->borderColor);
	//Graphics::Rectangle(screen, this->x - 3, this->y - 3, 6, 6, Graphics::red, Graphics::red);
}

int Circle::getSize() {
	return this->radius;
}

Vector2 Circle::getOffset()
{
	return Vector2{(double)this->radius,(double)this->radius};
}
