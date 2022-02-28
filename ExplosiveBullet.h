#pragma once
#include "Bullet.h"
#include "List.h"
class ExplosiveBullet :public Bullet{
private:
	List* bullets = nullptr;
public:
	ExplosiveBullet(Player* player, List* bullets,int speed, ColliderShape* shape, SDL_Surface* image = nullptr);
	virtual void collisionReact(int x, int y) override;
};

