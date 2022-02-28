#pragma once
#include "GameObject.h"
class Button : public GameObject{
private:
	const char* text;
	SDL_Surface* charset = nullptr;
	int fontSize = 16;
public:
	Button(const char* text, ColliderShape* shape, SDL_Surface* charset = nullptr, SDL_Surface* image = nullptr, int fontSize = 16);
	virtual void update(int offsetX, int offsetY, double delta = 0) override;
	virtual void draw(SDL_Surface* surface, int offsetX, int offsetY) override;
};

