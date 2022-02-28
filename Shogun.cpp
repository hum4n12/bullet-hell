#include "Shogun.h"
#define SHOGUN_SPEED 75
#define SHOGUN_HEALTH 10
#include <stdlib.h>
#include "Circle.h"
#include <stdio.h>

Shogun::Shogun(Player* player, List* bullets, int x, int y):Enemy(
	player,
	bullets,
	SHOGUN_SPEED,
	new Rectangle(x, y, 40, 100, Graphics::orange)
)
{
	this->animationOffset.x = 34;
	this->animationOffset.y = 45;
	this->hp = SHOGUN_HEALTH;
	this->timeToShoot = 1.5f;
}

void Shogun::shoot() {
	int bulletNum = rand() % 3 + 3;
	this->spreadAttack(bulletNum);
}

void Shogun::spreadAttack(int num) {
	int bulletsNumber = num;

	int x = *this->x;
	int y = *this->y;
	
	int pX = *this->player->shape->getX();
	int pY = *this->player->shape->getY();

	//double angle = M_PI/(180 / (bulletsNumber+1));
	double angle = M_PI / 180;
	angle *= (180 / (bulletsNumber + 1));
	double actualAngle = 0;

	double q = atan2(pY - y, pX - x);
	for (int i = 0; i < bulletsNumber; i++) {
		actualAngle += angle;

		int offsetX = sin(actualAngle + q) * 20;
		int offsetY = cos(actualAngle + q) * 20;
		GameObject* bullet = new Bullet(this->player, 300, new Circle(x + (sin(actualAngle)-1)*20, y + (cos(actualAngle)-1) * 20, BULLET_SIZE, Graphics::red));
		this->bullets->push(bullet);

		double radiusOffset = cos(actualAngle) / 2;
		
		if (q > 90 * (M_PI/180) && q < 270 * (M_PI / 180)) {
			radiusOffset = -radiusOffset;
		}

		bullet->update(0, 0, radiusOffset);
	}
}