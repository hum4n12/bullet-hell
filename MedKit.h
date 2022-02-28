#pragma once
#include "Enemy.h"
class MedKit : public Enemy{
public:
	MedKit(Player* player, List* bullets, int x, int y,SDL_Surface* img = nullptr);
	virtual void shoot() override;
	virtual void collisionReact(int x, int y) override;
};

