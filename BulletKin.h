#pragma once
#include "Enemy.h"
#include "Rectangle.h"

class BulletKin : public Enemy{
	//speed,collider shape, image
public:
	BulletKin(Player* player, List* bullets, int x, int y);
	virtual void shoot() override;
	~BulletKin();
};

