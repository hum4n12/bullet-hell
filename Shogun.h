#pragma once
#include "Enemy.h"
class Shogun :public Enemy{
private:
	void spreadAttack(int num = 4);
public:
	Shogun(Player* player, List* bullets, int x, int y);
	virtual void shoot() override;
};

