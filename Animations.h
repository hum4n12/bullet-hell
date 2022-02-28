#pragma once
#include "SDL2-2.0.10/include/SDL_surface.h"
#include "AnimationsList.h"
class Animations{
	const int runFrames = 6;
	const int attackFrames = 3;
	const int idleFrames = 6;
	SDL_Rect frame;
	SDL_Surface* run;
	SDL_Surface* attack;
	SDL_Surface* idle = nullptr;
	SDL_Surface* runFlip = nullptr;
	SDL_Surface* idleFlip = nullptr;
public:
	int getSize(int animation);
	Animations(SDL_Surface* run, SDL_Surface* attack, SDL_Surface* idle);
	void setFlip(SDL_Surface* runFlip, SDL_Surface* idleFlip = nullptr);
	SDL_Rect* getFrame(int animation,int Frame);
	SDL_Surface* getAnimation(int animation);
	SDL_Surface* getAnimationFlip(int animation);
};

