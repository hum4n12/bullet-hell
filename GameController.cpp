#include <stdio.h>
#include "GameController.h"

GameController::GameController() {
	this->title = "Explore the Gungeon";
	this->window = nullptr;
	this->renderer = nullptr;
	this->quit = 0;
	this->delta = 0;
	this->worldTime = 0;
	this->screen = nullptr;
	int playerX = SCREEN_WIDTH / 2 - 25;
	int playerY = SCREEN_HEIGHT / 2 - 25;
	
	this->camera.x = 0;
	this->camera.y = 0;
	this->camera.originX = playerX;
	this->camera.originY = playerY;
	this->player = new Player(&this->camera,new Rectangle(playerX, playerY, 50, 50, 0));
	//this->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
};

void GameController::init() {
	printf("%s", this->title);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return;
	}

	// tryb pe³noekranowy / fullscreen mode
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	int rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &this->window, &this->renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return;
	};
	this->screen = SDL_GetWindowSurface(this->window);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetWindowTitle(window, this->title);

	//creating a main list of objects
}

void GameController::update() {
	int t1 = SDL_GetTicks();
	int t2 = 0;
	int frameDelay = 1000 / MAX_FPS;

	int frameTime = 0;
	SDL_Rect r;
	
	GameObject* actual = nullptr;
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);

	Level level0(50,50,"./levels/0/","./levels/0/tileset.bmp",this->screen);
	this->camera.levelWidth = 50 * TILE_SIZE;
	this->camera.levelHeight = 50 * TILE_SIZE;

	while (!this->quit) {
		this->eventHandler();


		t2 = SDL_GetTicks();
		this->delta = (t2 - t1) * 0.001;
		this->worldTime += this->delta;
		t1 = t2;

		SDL_FillRect(this->screen, NULL, niebieski);
		this->player->update(this->delta,0,0);


		/*DRAWING*/
		for (int i = 0; i < this->gameObjects.getSize(); i++) {
			actual = this->gameObjects.get(i);
			actual->draw(this->screen);
		}

		level0.draw(this->camera);
		this->player->draw(this->screen);
		






		/*END DROWING*/
		SDL_UpdateWindowSurface(this->window);

		frameTime = SDL_GetTicks() - t2;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

}

void GameController::eventHandler() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		this->player->controls(event);
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) this->quit = 1;
			/*else if (event.key.keysym.sym == SDLK_UP) etiSpeed = 2.0;
			else if (event.key.keysym.sym == SDLK_DOWN) etiSpeed = 0.3;*/
			break;
		case SDL_KEYUP:
			//etiSpeed = 1.0;
			break;
		case SDL_QUIT:
			this->quit = 1;
			break;
		};
	};
	//frames++;
}

void GameController::clean() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	SDL_Quit();
}