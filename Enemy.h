#pragma once

#include "GameObject.h"
#include "Player.h"
#include "GLOBALS.h"
#include "List.h"
#include "Bullet.h"

class Enemy : public GameObject{
protected:
	Player* player = nullptr;
	double timer = 0;
	double timeToShoot = 0.5f;
	List* bullets = nullptr;
	Camera* camera = nullptr;
	double delta = 0;

public:
	double atan2Angle = 0;
	Enemy(Player* player,List* bullets,int speed,ColliderShape* shape, SDL_Surface* image = nullptr);
	void setDirection();
	virtual void update(int offsetX, int offsetY, double delta = 0) override;
	void time(double delta) override;
	virtual void shoot() = 0;
};