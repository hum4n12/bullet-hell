#include "Level.h"
#include "Graphics.h"
#include "Wall.h"
#include "Rectangle.h"
#include <stdio.h>
#include <string.h>

Level::Level(int width, int height, const char* filePath,const char* tileSetPath, SDL_Surface* screen,Player* player){
	this->width = width;
	this->height = height;
	this->filePath = filePath;
	this->tileSetPath = tileSetPath;
	this->tiles = nullptr;
	this->tilesSize = 0;
	this->screen = screen;
	this->player = player;
	this->load();
}

bool Level::load() {
	SDL_Surface* image = nullptr;
	printf("%s", this->tileSetPath);
	//Graphics::loadImage(this->tileSetPath, image);
	image = SDL_LoadBMP(this->tileSetPath);
	image = SDL_ConvertSurface(image, this->screen->format, 0);

	int columns = image->w / TILE_SIZE;
	int rows = image->h / TILE_SIZE;
	this->tilesSize = columns * rows;

	this->tiles = new Tile[this->tilesSize];

	Tile* temp;
	Vector2 rect;
	rect.x = 0;
	rect.y = 0;


	//loading tileset
	//array iterator
	int i = 0;
	for (int r = 0; r < rows; r++) {
		rect.x = 0;
		for (int c = 0; c < columns; c++) {
			temp = new Tile(rect.x, rect.y, this->screen, image);
			this->tiles[i] = *temp;
			rect.x += TILE_SIZE;
			i++;
		}
		rect.y += TILE_SIZE;
	}

	//loading csv level data
	this->dataSize = this->width * this->height;

	char path[MAX_PATH_LENGTH];
	strcpy(path, this->filePath);
	strcat(path, this->base);

	this->displayData = Graphics::loadCSV(path, this->dataSize);

	return true;
}

void Level::draw(Camera* camera) {
	Vector2 rect;
	rect.x = 0;
	rect.y = 0;
	int i = 0;
	int goIterator = 0;
	GameObject* temp = nullptr;
	for (int r = 0; r < this->height; r++) {
		rect.x = 0;
		for (int c = 0; c < this->width; c++) {
			int tile = this->displayData[i];
			int collider = this->collisionData[i];
			int destX = rect.x;
			int destY = rect.y;
			destX -= camera->x;
			destY -= camera->y;

			if (collider >= 0) {
				temp = this->gameObjects.get(goIterator);
				temp->update(destX + TILE_SIZE / 2 , destY + TILE_SIZE / 2);
				goIterator++;
			}

			if (destX >= 0 - TILE_SIZE && destX <= SCREEN_WIDTH + TILE_SIZE 
				&& destY >= 0 - TILE_SIZE && destY <= SCREEN_HEIGHT+ TILE_SIZE) {
				//this->tiles[tile].draw(destX, destY);
				temp->draw(this->screen,TILE_SIZE/2,TILE_SIZE/2);
			}
			rect.x += TILE_SIZE;
			i++;
		}
		rect.y += TILE_SIZE;
	}
}

void Level::init(){
	char path[MAX_PATH_LENGTH];

	strcpy(path, this->filePath);
	strcat(path, this->colliders);

	//loading csv level data
	this->collisionData = Graphics::loadCSV(path, this->dataSize);

	Vector2 rect;
	rect.x = 0;
	rect.y = 0;
	int i = 0;
	for (int r = 0; r < this->height; r++) {
		rect.x = 0;
		for (int c = 0; c < this->width; c++) {
			int tile = this->collisionData[i];
			int destX = rect.x;
			int destY = rect.y;
			if (tile >= 0) {
				GameObject* temp = new Wall(new Rectangle(destX, destY, TILE_SIZE, TILE_SIZE, 0));
				this->gameObjects.push(temp);
			}
			rect.x += TILE_SIZE;
			i++;
		}
		rect.y += TILE_SIZE;
	}
}
void Level::horizontalMovementCollision(double delta) {
	this->player->horizontalMovement(delta);

	for (int i = 0; i < this->gameObjects.getSize(); i++) {
		GameObject* go = this->gameObjects.get(i);
		printf("%d",go->collision(this->player, this->screen));
	}
}

void Level::verticalMovementCollision(double delta) {
	this->player->verticalMovement(delta);

	for (int i = 0; i < this->gameObjects.getSize(); i++) {
		GameObject* go = this->gameObjects.get(i);
		go->collision(this->player, this->screen);
	}
}

void Level::update(Camera* camera,double delta) {
	this->horizontalMovementCollision(delta);
	this->verticalMovementCollision(delta);
}