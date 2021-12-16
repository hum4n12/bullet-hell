#pragma once
#include "./SDL2-2.0.10/include/SDL.h"
#define TILE_SIZE 64
class Tile{
private:
	SDL_Rect src, dest;
	SDL_Surface* screen;
	SDL_Surface* tileset;
public:
	Tile();
	//x, y -> starting point for blitting
	Tile(int x,int y,SDL_Surface* screen, SDL_Surface* tileset);
	void draw(int x,int y);
};

