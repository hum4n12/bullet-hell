#include "Tile.h"
#include "Graphics.h"

Tile::Tile() {
	this->src.x = 0;
	this->src.y = 0;
	this->src.w = TILE_SIZE;
	this->src.h = TILE_SIZE;
	this->screen = nullptr;
	this->tileset = nullptr;
}

Tile::Tile(int x, int y, SDL_Surface* screen,SDL_Surface* tileset) {
	this->src.x = x;
	this->src.y = y;
	this->src.w = TILE_SIZE;
	this->src.h = TILE_SIZE;
	this->screen = screen;
	this->tileset = tileset;
}

void Tile::draw(int x,int y){
	Graphics::Surface(this->screen, this->tileset, x, y, &this->src,false);
}