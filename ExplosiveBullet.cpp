#include "ExplosiveBullet.h"
#include "Circle.h"

ExplosiveBullet::ExplosiveBullet(Player* player,List* bullets ,int speed, ColliderShape* shape, SDL_Surface* image):Bullet(player,speed,shape,image){
	this->bullets = bullets;
}

void ExplosiveBullet::collisionReact(int x, int y){
	int bulletsNumber = 8;

	x = *this->x;
	y = *this->y;

	//double angle = M_PI/(180 / (bulletsNumber+1));
	double angle = M_PI / 180;
	angle *= 45;
	double actualAngle = 0;

	double q = 0;
	for (int i = 0; i < bulletsNumber; i++) {

		int offsetX = sin(actualAngle) * 20;
		int offsetY = cos(actualAngle) * 20;
		GameObject* bullet = new Bullet(Vector2{ (double)x,(double)y },M_PI, 300, new Circle(x + (sin(actualAngle)) * 20, y + (cos(actualAngle)) * 20, BULLET_SIZE, Graphics::red));
		this->bullets->push(bullet);

		bullet->update(0, 0, 0);

		actualAngle += angle;
	}

}