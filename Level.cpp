#include "Level.h"
#include "Graphics.h"
#include "Wall.h"
#include "Rectangle.h"
#include <stdio.h>
#include <string.h>
#include "EnemiesList.h"
#include "BulletKin.h"
#include "Shogun.h"
#include "Fuselier.h"
#include "Knight.h"
#include "MedKit.h"
#define DEFAULT_PATH "./graphics/"
#define BULLET_KIN_ANIMATIONS "./graphics/animations/bullet_kin/"
#define SHOGUN_ANIMATIONS "./graphics/animations/shogun/"
#define FUSELIER_ANIMATIONS "./graphics/animations/fuselier/"
#define KNIGHT_ANIMATIONS "./graphics/animations/knight/"
#define PLAYER_ANIMATIONS "./graphics/animations/player/"
#define MEDKIT_CHANCE_DROP 20 //%

Level::Level(int width, int height, const char* filePath,const char* tileSetPath, SDL_Surface* screen,Player* player,Camera* camera){
	this->width = width;
	this->height = height;
	this->filePath = filePath;
	this->tileSetPath = tileSetPath;
	this->tiles = nullptr;
	this->tilesSize = 0;
	this->screen = screen;
	this->player = player;
	this->camera = camera;
	this->load();
	this->medKitImg = Graphics::loadImage(DEFAULT_PATH"medkit.bmp");
}

bool Level::load() {
	if (this->tileset != nullptr) {
		SDL_FreeSurface(this->tileset);
		delete this->tileset;
	}
	
	//Graphics::loadImage(this->tileSetPath, image);
	this->tileset = SDL_LoadBMP(this->tileSetPath);
	this->tileset = SDL_ConvertSurface(this->tileset, this->screen->format, 0);

	int columns = this->tileset->w / TILE_SIZE;
	int rows = this->tileset->h / TILE_SIZE;
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
			temp = new Tile(rect.x, rect.y, this->screen, this->tileset);
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

void Level::init() {
	//

	Animations* bullet_kin = new Animations(Graphics::loadImage(BULLET_KIN_ANIMATIONS"run.bmp"),nullptr,nullptr);
	bullet_kin->setFlip(Graphics::loadImage(BULLET_KIN_ANIMATIONS"run_flip.bmp"));

	Animations* shogun = new Animations(Graphics::loadImage(SHOGUN_ANIMATIONS"run.bmp"),nullptr,nullptr);
	shogun->setFlip(Graphics::loadImage(SHOGUN_ANIMATIONS"run_flip.bmp"));

	Animations* fuselier = new Animations(Graphics::loadImage(FUSELIER_ANIMATIONS"run.bmp"),nullptr,nullptr);
	fuselier->setFlip(Graphics::loadImage(FUSELIER_ANIMATIONS"run_flip.bmp"));

	Animations* knight = new Animations(Graphics::loadImage(KNIGHT_ANIMATIONS"run.bmp"),nullptr,nullptr);
	knight->setFlip(Graphics::loadImage(KNIGHT_ANIMATIONS"run_flip.bmp"));


	this->player->initAnimations();
	this->player->animations->setFlip(Graphics::loadImage(PLAYER_ANIMATIONS"run_flip.bmp"), Graphics::loadImage(PLAYER_ANIMATIONS"idle_flip.bmp"));

	this->camera->setLevelDimensions(this->width * TILE_SIZE, this->height * TILE_SIZE);
	char path[MAX_PATH_LENGTH];

	strcpy(path, this->filePath);
	strcat(path, this->colliders);

	//loading csv level data
	this->collisionData = Graphics::loadCSV(path, this->dataSize);

	//loading enemy data
	strcpy(path, "");
	strcpy(path, this->filePath);
	strcat(path, this->enemiesFile);
	this->enemyData = Graphics::loadCSV(path, this->dataSize);

	Vector2 rect;
	rect.x = 0;
	rect.y = 0;
	int i = 0;
	for (int r = 0; r < this->height; r++) {
		rect.x = 0;
		for (int c = 0; c < this->width; c++) {
			int tile = this->collisionData[i];
			int enemy = this->enemyData[i];
			int destX = rect.x;
			int destY = rect.y;
			if (tile >= 0) {
				destX -= TILE_SIZE/2;
				destY -= TILE_SIZE/2;
				GameObject* temp = new Wall(new Rectangle(destX, destY, TILE_SIZE, TILE_SIZE, 0));
				this->walls.push(temp);
			}
			
			destX = rect.x;
			destY = rect.y;
			if (enemy >= 0) {
				EnemiesList e;
				GameObject* temp = nullptr;
				switch (enemy) {
				case PLAYER:
					this->player->setCoords(destX, destY);
					break;
				case MED_KIT:
					temp = new MedKit(this->player, &this->bullets, destX, destY,this->medKitImg);
					break;
				case BULLET_KIN:
					temp = new BulletKin(this->player, &this->bullets, destX, destY);
					temp->initAnimations(bullet_kin);
					break;
				case SHOGUN:
					temp = new Shogun(this->player, &this->bullets, destX, destY);
					temp->initAnimations(shogun);
					break;
				case FUSELIER:
					temp = new Fuselier(this->player, &this->bullets, destX, destY);
					temp->initAnimations(fuselier);
					break;
				case KNIGHT:
					temp = new Knight(this->player, &this->bullets, destX, destY);
					temp->initAnimations(knight);
					break;
				default:
					temp = new BulletKin(this->player, &this->bullets, destX, destY);
					break;
				}
				if (temp != nullptr) {
					Vector2 offset = temp->shape->getOffset();
					temp->addCoords(-offset.x, -offset.y);
					this->enemies.push(temp);
				}
			}
			rect.x += TILE_SIZE;
			i++;
		}
		rect.y += TILE_SIZE;
	}
}

void Level::draw(Camera* camera) {
	Vector2 rect;
	rect.x = 0;
	rect.y = 0;
	int i = 0;
	int goIterator = 0;
	int enemyIterator = 0;
	GameObject* temp = nullptr;
	
	for (int r = 0; r < this->height; r++) {
		rect.x = 0;
		for (int c = 0; c < this->width; c++) {
			int tile = this->displayData[i];
			int collider = this->collisionData[i];
			int enemy = this->enemyData[i];
			int destX = rect.x;
			int destY = rect.y;

			if (collider >= 0) {
				temp = this->walls.get(goIterator);
				destX = *temp->shape->getX() - camera->x;
				destY = *temp->shape->getY() - camera->y;

				temp->setCoords(destX , destY);
				goIterator++;
			}

			destX = rect.x - camera->originX + SCREEN_WIDTH/2 - TILE_SIZE /2;
			destY = rect.y - camera->originY + SCREEN_HEIGHT/2 - TILE_SIZE/2;

			if (destX >= 0 - TILE_SIZE && destX <= SCREEN_WIDTH + TILE_SIZE 
				&& destY >= 0 - TILE_SIZE && destY <= SCREEN_HEIGHT+ TILE_SIZE) {
				this->tiles[tile].draw(destX, destY);
				temp->draw(this->screen,32,32);
			}
			rect.x += TILE_SIZE;
			i++;
		}
		rect.y += TILE_SIZE;
	}
	for (int i = 0; i < this->enemies.getSize(); i++) {
		GameObject* go = this->enemies.get(i);
		int destX = *go->shape->getX() - camera->x;
		int destY = *go->shape->getY() - camera->y;
		go->setCoords(destX, destY);
		if (
			abs(destX - *this->player->shape->getX()) <= SCREEN_WIDTH &&
			abs(destY - *this->player->shape->getY()) <= SCREEN_HEIGHT) {

			Vector2 offset = go->shape->getOffset();
			go->draw(this->screen,(int)offset.x, (int)offset.y);
		}
		/*printf("\n%d", go->getDirection().x);*/
	}
	for (int i = 0; i < this->bullets.getSize(); i++) {
		GameObject* bullet = this->bullets.get(i);
		if (bullet != nullptr) {
			int destX = *bullet->shape->getX() - camera->x;
			int destY = *bullet->shape->getY() - camera->y;
			bullet->setCoords(destX, destY);
			bullet->draw(this->screen, 0, 0);
		}
	}
	//this->player->addCoords(-camera->x, -camera->y);
}

void Level::horizontalEnemyCollision(GameObject* go) {
	int offset = 0;
	for (int i = 0; i < this->enemies.getSize(); i++) {
		GameObject* enemy = this->enemies.get(i);
		if (go->collision(enemy)) {
			enemy->collisionReact(0, 0);
			Vector2 enemyOffset = enemy->shape->getOffset();
			Vector2 goOffset = go->shape->getOffset();
			offset = (int)enemyOffset.x + (int)goOffset.x;
			if (enemy->getDirection().x < 0) {
				enemy->setX(*go->shape->getX() + offset);
			}
			else if (enemy->getDirection().x > 0) {
				enemy->setX(*go->shape->getX() - offset);
			}
		}
	}
}

void Level::verticalEnemyCollision(GameObject* go) {
	int offset = 0;
	for (int i = 0; i < this->enemies.getSize(); i++) {
		GameObject* enemy = this->enemies.get(i);
		if (go->collision(enemy)) {
			Vector2 enemyOffset = enemy->shape->getOffset();
			Vector2 goOffset = go->shape->getOffset();
			enemy->collisionReact(0, 0);
			offset = (int)enemyOffset.y + (int)goOffset.y;
			if (enemy->getDirection().y < 0) {
				enemy->setY(*go->shape->getY() + offset);
			}
			else if (enemy->getDirection().y > 0) {
				enemy->setY(*go->shape->getY() - offset);
			}
		}
	}
}

void Level::horizontalMovementCollision(double delta) {
	this->player->horizontalMovement(delta);

	for (int i = 0; i < this->enemies.getSize(); i++) {
		GameObject* enemy = this->enemies.get(i);
		enemy->update(this->camera->x, 0, delta);
		enemy->horizontalMovement(delta);
		/*printf("\n%d", go->getDirection().x);*/
	}

	Vector2 playerDirection = this->player->getDirection();

	int offset = 0;

	for (int i = 0; i < this->walls.getSize(); i++) {
		GameObject* go = this->walls.get(i);

		this->horizontalEnemyCollision(go);

		if (go->collision(this->player)) {
			Vector2 playerOffset = this->player->shape->getOffset();
			Vector2 goOffset = go->shape->getOffset();
			offset = (int)playerOffset.x + (int)goOffset.x;
			if (playerDirection.x < 0) {
				this->player->setX(*go->shape->getX() + offset);
			}
			else if (playerDirection.x > 0) {
				this->player->setX(*go->shape->getX() - offset);
			}
		}
	}
}

void Level::verticalMovementCollision(double delta) {
	this->player->verticalMovement(delta);
	Vector2 playerDirection = this->player->getDirection();

	for (int i = 0; i < this->enemies.getSize(); i++) {
		GameObject* enemy = this->enemies.get(i);
		enemy->update(0, this->camera->y, delta);
		enemy->verticalMovement(delta);
		/*printf("\n%d", go->getDirection().x);*/
	}

	int offset = 0;

	for (int i = 0; i < this->walls.getSize(); i++) {
		GameObject* go = this->walls.get(i);

		this->verticalEnemyCollision(go);

		if (go->collision(this->player)) {
			Vector2 playerOffset = this->player->shape->getOffset();
			Vector2 goOffset = go->shape->getOffset();
			offset = (int)playerOffset.y + (int)goOffset.y;
			if (playerDirection.y < 0) {
				this->player->setY(*go->shape->getY() + offset);
			}
			else if (playerDirection.y > 0) {
				this->player->setY(*go->shape->getY() - offset);
			}
		}
	}
}

void Level::update(Camera* camera,double delta) {
	this->horizontalMovementCollision(delta);
	this->verticalMovementCollision(delta);
	this->player->update(0,0,delta);
	this->bulletsUpdate(delta);
	this->checkEnemyDeath();
	this->enemyPlayerCollision();
	camera->update();
	this->player->addCoords(-camera->x, -camera->y);
	//printf("\n%d", this->bullets.getSize());
}

void Level::shoot(double delta) {
	for (int i = 0; i < this->enemies.getSize(); i++) {
		GameObject* enemy = this->enemies.get(i);
		enemy->time(delta);
	}
}

void Level::bulletsUpdate(double delta){
	for (int i = 0; i < this->bullets.getSize(); i++) {
		GameObject* bullet = this->bullets.get(i);
		if (bullet != nullptr) {
			bullet->horizontalMovement(delta);
			bullet->verticalMovement(delta);
		}
	}
	
	for (int i = this->bullets.getSize()-1; i >= 0; i--) {
		//printf("\n%d", i);
		GameObject* bullet = this->bullets.get(i);
		
		for (int j = 0; j < this->walls.getSize(); j++) {
			GameObject* wall = this->walls.get(j);
			if (wall->collision(bullet)) {
				bullet->collisionReact(0,0);
				this->bullets.remove(i);
				delete bullet;
				bullet = nullptr;
				break;
			}
		}

		if (bullet != nullptr) {
			if (bullet->customFlag == 0) {
				if (this->player->collision(bullet)) {
					this->player->hit();
					bullet->collisionReact(0, 0);
					this->bullets.remove(i);
					delete bullet;
					continue;
				}
			}

			for (int j = 0; j < this->enemies.getSize(); j++) {
				GameObject* enemy = this->enemies.get(j);
				if (bullet->customFlag == 1 && enemy->collision(bullet)) {
					enemy->hp--;
					enemy->drawingHit = 0.7;
					this->player->updateScore(1);
					bullet->collisionReact(0, 0);
					this->bullets.remove(i);
					delete bullet;
					break;
				}
			}
		}
	}
}

void Level::enemyPlayerCollision() {
	for (int i = 0; i < this->enemies.getSize(); i++) {
		GameObject* go = this->enemies.get(i);
		if (go->collision(this->player)) {
			go->collisionReact(0, 0);
			this->player->hit(go->getHitValue());
		}
	}
}

void Level::checkEnemyDeath() {
	int medKits = 0;
	bool isMedKit = 0;
	for (int i = this->enemies.getSize()-1; i >= 0; i--) {
		GameObject* go = this->enemies.get(i);
		if (go->getHitValue() < 0) {
			medKits++;
			isMedKit = true;
		}
		if (go->isDead()) {
			if (isMedKit == false) {
				int chance = rand() % 100 + 1;
				if (chance <= MEDKIT_CHANCE_DROP) {
					this->enemies.push(new MedKit(this->player, &this->bullets, *go->shape->getX(), *go->shape->getY(), this->medKitImg));
					medKits++;
				}
			}
			else
			{
				medKits--;
			}
			this->enemies.remove(i);
			delete go;
		}
		isMedKit = false;
	}
	if (this->enemies.getSize() == 0 || medKits == this->enemies.getSize()) {
		this->finished = 1;
	}
}

bool Level::isFinished(){
	return this->finished;
}

List* Level::getPlayerBullets(){
	return &this->bullets;
}
