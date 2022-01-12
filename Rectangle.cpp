#include "Rectangle.h"
#include <stdio.h>
Rectangle::Rectangle(int x,int y, int width, int height, Uint32 color) {
	this->x = x + width / 2;
	this->y = y + height / 2;
	this->width = width;
	this->height = height;
	this->color = color;
}

//collider.x < x2 + w2 and x2 < collider.x + collider.width and

bool Rectangle::collision(int x, int y) {
	int hw = this->width / 2;
	int hh = this->height / 2;
	
	if (x > this->x - hw && x < this->x + hw && y > this->y - hh && y < this->y + hh) return true;
	return false;
}

Vector2 Rectangle::nearestPoint(int x, int y) {
	Vector2 pos;
	int hw = this->width / 2;
	int hh = this->height / 2;
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

void Rectangle::setColliderPoint(int x, int y) {
	if(x >= 0)
		this->x = x;
	if (y >= 0)
		this->y = y;
}

void Rectangle::draw(SDL_Surface* screen, int offsetX, int offsetY) {
	this->color = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	Graphics::Rectangle(screen,this->x-offsetX,this->y-offsetY,this->width,this->height,this->color,this->color);
}