#pragma once
#include "GameObject.h"
#include "Player.h"

class Bullet : public GameObject{
protected:
	Player* player = nullptr;
	Vector2 directionSetter = { 0,0 };
	double angleOffset = 0;
public:
	Bullet(Player* player, int speed, ColliderShape* shape, SDL_Surface* image = nullptr);
	Bullet(Vector2 dir, int speed, ColliderShape* shape, SDL_Surface* image = nullptr, bool playerBullet = 0);
	Bullet(Vector2 dir, double angleOffset, int speed, ColliderShape* shape, SDL_Surface* image=nullptr);
	void setDirection(double radiusOffset = 0);
	void update(int offsetX, int offsetY, double radiusOffset = 0) override;
	~Bullet();
	virtual void collisionReact(int x, int y) override;
};