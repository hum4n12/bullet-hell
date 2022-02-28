#include "Zone.h"

Zone::Zone(ColliderShape* shape, SDL_Surface* warning, SDL_Surface* attack) :GameObject(shape, nullptr) {
	//this->warning = warning;
	this->attack = attack;
	this->image = nullptr;
	this->shape->changeColor(Graphics::cyan);
}

void Zone::update(int x, int y, double delta) {
	if(!danger) this->timer += delta;
	if (this->timer >= this->timeToDanger) {
		this->danger = 1;
		this->image = attack;
	}

	if (this->danger) {
		this->timer -= delta;
		if (this->timer < 0) {
			this->customFlag = 1;
		}
	}
}