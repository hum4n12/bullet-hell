#pragma once
#include "Enemy.h"
class Fuselier :public Enemy{
private:
	double bigBulletTimer = 0;
	bool bigBulletTimerFlag = 0;
	GameObject* lastBullet = nullptr;
	void bigBulletAttack();
	void explosionAttack();
public:
	Fuselier(Player* player, List* bullets, int x, int y);
	virtual void shoot() override;
	virtual void update(int offsetX, int offsetY, double delta) override;
};

