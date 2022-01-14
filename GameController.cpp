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
	this->player = nullptr;
	this->camera = nullptr;
	this->currentLevel = nullptr;
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


void GameController::start() {
	int playerX = SCREEN_WIDTH / 2;
	int playerY = SCREEN_HEIGHT / 2;

	delete this->currentLevel;
	delete this->player;
	delete this->camera;


	this->player = new Player(this->camera, new Rectangle(playerX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT, 0));
	this->camera = new Camera(this->player);
	this->currentLevel = new Level(36, 30, "./levels/0/", "./levels/0/tileset.bmp", this->screen, this->player, this->camera);
	this->currentLevel->init();
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

	//Level level0(50,50,"./levels/0/","./levels/0/tileset.bmp",this->screen,this->player,this->camera);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);

	this->start();
	while (!this->quit) {
		this->eventHandler();

		t2 = SDL_GetTicks();
		this->delta = (t2 - t1) * 0.001;
		this->worldTime += this->delta;
		t1 = t2;

		SDL_FillRect(this->screen, NULL, czarny);
		
		//this->player->update(0, 0, this->delta);
		this->currentLevel->update(this->camera,this->delta);
		this->currentLevel->draw(this->camera);
		//this->player->draw(this->screen, this->camera->x,this->camera->y);
		this->player->draw(this->screen, 25 ,25);
		this->currentLevel->shoot(delta);

		Graphics::Rectangle(screen, *this->player->shape->getX() - 3, *this->player->shape->getY() - 3, 6, 6, czerwony, czerwony);

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
			if (event.key.keysym.sym == SDLK_n) {
				this->start();
			}
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