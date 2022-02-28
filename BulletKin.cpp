#include "BulletKin.h"
#include "Circle.h"
#include <stdio.h>
#include <string.h>
#define BULLET_KIN_SPEED 75
#define BULLET_KIN_HEALTH 6
// int speed, ColliderShape* shape,
BulletKin::BulletKin(Player* player, List* bullets, int x, int y):Enemy(
	player,
	bullets,
	BULLET_KIN_SPEED,
	new Rectangle(x, y, 45, 70, Graphics::yellow)
)
{
	this->animationOffset.x = 20;
	this->animationOffset.y = 38;
	this->hp = BULLET_KIN_HEALTH;
	this->timeToShoot = 1.0f;
}

void BulletKin::shoot() {
	GameObject* bullet = new Bullet(this->player, BULLET_SPEED, new Circle(*this->x, *this->y, BULLET_SIZE, Graphics::red));
	this->bullets->push(bullet);
	bullet->update(0, 0, 0); //updating direction
}

