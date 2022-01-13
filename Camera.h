#pragma once

class Player;
class Camera{
public:
	int x = 0;
	int y = 0;
	int originX = 0;
	int originY = 0;

	int left = 0;
	int right = 0;
	int top = 0;
	int bottom = 0;

	int offsetX = 0;
	int offsetY = 0;
	Player* player;

	Camera(Player* player);
	void update();
	void setLevelDimensions(int levelWidth, int levelHeight);
};
#include "Player.h"