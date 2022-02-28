#pragma once
#include "GameObject.h"
class Zone :public GameObject{
private:
	double timer = 0;
	double const timeToDanger = 0.3f;
	bool danger = 0;
	//SDL_Surface* warning = nullptr;
	SDL_Surface* attack = nullptr;
public:
	Zone(ColliderShape* shape, SDL_Surface* warning, SDL_Surface* attack);
	virtual void update(int x, int y, double delta = 0);
};