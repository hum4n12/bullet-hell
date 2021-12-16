#pragma once

class Player;
class Camera{
public:
	int x;
	int y;
	int originX;
	int originY;
	bool follow = true;
	int levelWidth = 0;
	int levelHeight = 0;

	void update(int x,int y,Player* player);
};
#include "Player.h"