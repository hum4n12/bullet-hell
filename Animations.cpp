#include "Animations.h"

Animations::Animations(SDL_Surface* run, SDL_Surface* attack, SDL_Surface* idle):run(run),attack(attack),idle(idle){

}

void Animations::setFlip(SDL_Surface* runFlip, SDL_Surface* idleFlip){
	this->runFlip = runFlip;
	this->idleFlip = idleFlip;
}

SDL_Rect* Animations::getFrame(int animation, int Frame)
{
	int frames = 0;
	SDL_Surface* curr = nullptr;
	switch (animation) {
	case RUN:
		frames = this->runFrames;
		curr = this->run;
		break;
	case ATTACK:
		frames = this->attackFrames;
		curr = this->attack;
		break;
	case IDLE:
		frames = this->idleFrames;
		curr = this->idle;
		break;
	}
	if (curr != nullptr) {
		this->frame.w = curr->w / frames;
		this->frame.x = (this->frame.w * Frame)-this->frame.w;
		this->frame.y = 0;
		this->frame.h = curr->h;
	}

	return &this->frame;
}

SDL_Surface* Animations::getAnimation(int animation)
{
	SDL_Surface* surf = nullptr;
	switch (animation) {
	case RUN:
		surf = this->run;
		break;
	case ATTACK:
		surf = this->attack;
		break;
	case IDLE:
		surf = this->idle;
		break;
	}
	return surf;
}

SDL_Surface* Animations::getAnimationFlip(int animation)
{
	SDL_Surface* surf = nullptr;
	switch (animation) {
	case RUN:
		if (this->runFlip != nullptr)
			surf = this->runFlip;
		else surf = this->run;
		break;
	case ATTACK:
		surf = this->attack;
		break;
	case IDLE:
		surf = this->idleFlip;
		break;
	}
	return surf;
}

int Animations::getSize(int animation) {
	int size = 0;
	switch (animation) {
	case RUN:
		size = this->runFrames;
		break;
	case ATTACK:
		size = this->attackFrames;
		break;
	case IDLE:
		size = this->idleFrames;
		break;
	}

	return size;
}
