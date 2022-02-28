#pragma once
#include "Enemy.h"
#include "List.h"
class Knight :public Enemy{
private:
	double attackDelayTimer = 0;
	double attackDelayFlag = 0;
	SDL_Surface* attackZone = nullptr;
	SDL_Surface* warningZone = nullptr;

	List zones;
	void horizontalAttack();
	void verticalAttack();
public:
	Knight(Player* player, List* bullets, int x, int y);
	virtual void update(int x, int y, double delta);
	virtual void draw(SDL_Surface* screen, int offsetX = 0, int offsetY = 0) override;
	virtual void shoot() override;
};