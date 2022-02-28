#include "MedKit.h"
#define MED_KIT_SIZE 30

MedKit::MedKit(Player* player, List* bullets, int x, int y,SDL_Surface* img) :Enemy(
	player,
	bullets,
	0,
	new Rectangle(x, y, MED_KIT_SIZE, MED_KIT_SIZE, Graphics::red),
	img
)
{
	this->image = img;
	this->hitValue = -1;
	this->hp = 4;
}


void MedKit::shoot()
{
}

void MedKit::collisionReact(int x, int y)
{
	this->hp = 0;
}
