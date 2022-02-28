#include "Button.h"
#include <stdio.h>

Button::Button(const char* text, ColliderShape* shape, SDL_Surface* charset,SDL_Surface* image,int fontSize):GameObject(shape,image){
	this->text = text;
	this->charset = charset;
	this->image = image;
	this->fontSize = fontSize;
}

void Button::update(int offsetX, int offsetY, double delta){
}

void Button::draw(SDL_Surface* surface, int offsetX, int offsetY) {
	Vector2 offset = this->shape->getOffset();
	//this->shape->draw(surface, offset.x, offset.y);
	if (this->image != nullptr) {
		Graphics::Surface(surface, this->image, *this->x, *this->y, nullptr);
	}
	Graphics::String(surface, *this->x- offset.x, *this->y - FONT_SIZE/2, this->text, this->charset,this->fontSize);
}