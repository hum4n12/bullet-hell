#include "Rectangle.h"

Rectangle::Rectangle(int x,int y, int width, int height, Uint32 color) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->color = color;
}

//collider.x < x2 + w2 and x2 < collider.x + collider.width and
bool Rectangle::collision(int* cx, int* cy) {
	int x = *cx;
	int y = *cy;
	if (cx == nullptr && cy == nullptr) return false;
	//checking if collider x is between left and right side of rectangle
	if (cy == nullptr) {
		return (x < this->x + this->width && x > this->x);
	}
	if (cx == nullptr) {
		return (y < this->y + this->height && y > this->y);
	}
	else{
		return (x < this->x + this->width && x > this->x && y < this->y + this->height && y > this->y);
	}
	return false;
}

void Rectangle::draw(SDL_Surface* screen) {
	this->color = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	Graphics::Rectangle(screen,this->x,this->y,this->width,this->height,this->color,this->color);
}

int Rectangle::getWidth() {
	return this->width;
}

int Rectangle::getHeight() {
	return this->height;
}