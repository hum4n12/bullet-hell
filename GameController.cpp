#include <stdio.h>
#include "GameController.h"
#include "States.h"
#include "Button.h"
#define HEALTHBAR_WIDTH 313

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
	this->charset = Graphics::loadImage("./graphics/cs8x8.bmp");
	this->mainMenuBackground = Graphics::loadImage("./graphics/main_menu.bmp");
	this->levelMenuBackground = Graphics::loadImage("./graphics/menu.bmp");
	this->healthBar = Graphics::loadImage("./graphics/healthbar.bmp");
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
	int rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_RENDERER_PRESENTVSYNC, &this->window, &this->renderer);
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
	this->load();
}

void GameController::mainMenu() {
	Graphics::Surface(this->screen, this->mainMenuBackground, 0, 0,nullptr,false);

	for (int i = 0; i < this->buttons.getSize(); i++) {
		GameObject* button = this->buttons.get(i);
		
		if (button->shape->collision(mousePos.x,mousePos.y)) {
			switch (i) {
			case 0:
				this->changeState(GAME);
				return;
				break;
			case 1:
				this->changeState(LEVEL_MENU);
				return;
				break;
			case 2:
				this->quit = 1;
				this->buttons.clear();
				return;
				break;
			};
		}

	}

	for (int i = 0; i < this->buttons.getSize(); i++) {
		GameObject* button = this->buttons.get(i);
		button->draw(this->screen);
	}
}

void GameController::levelMenu() {
	Graphics::Surface(this->screen, this->levelMenuBackground, 0, 0, nullptr, false);

	for (int i = 0; i < this->buttons.getSize(); i++) {
		GameObject* button = this->buttons.get(i);

		if (button->shape->collision(mousePos.x, mousePos.y)) {
			switch (i) {
			case 0:
				this->changeState(MAIN_MENU);
				return;
				break;
			case 1:
				this->quit = 1;
				this->buttons.clear();
				return;
				break;
			default:
				this->levelNum = i - 1;
				this->changeState(GAME);
				return;
				break;
			};
		}

	}

	for (int i = 0; i < this->buttons.getSize(); i++) {
		GameObject* button = this->buttons.get(i);
		button->draw(this->screen);
	}
}

void GameController::changeState(int x){
	this->state = x;
	this->buttons.clear();
	this->load();
}

void GameController::loadMainMenu(){
	//play button	
	this->buttons.push(new Button("Quick start",new Rectangle(50,550,11*FONT_SIZE,25,Graphics::red),this->charset));
	this->buttons.push(new Button("Levels",new Rectangle(50,600,6*FONT_SIZE,25,0),this->charset));
	this->buttons.push(new Button("Quit",new Rectangle(50,650,4*FONT_SIZE,25,0),this->charset));
}

void GameController::loadLevelMenu() {
	this->numbers[0] = Graphics::loadImage("./graphics/numbers/1.bmp");
	this->numbers[1] = Graphics::loadImage("./graphics/numbers/2.bmp");
	this->numbers[2] = Graphics::loadImage("./graphics/numbers/3.bmp");

	this->buttons.push(new Button("Back", new Rectangle(50, 600, 4 * FONT_SIZE, 25, Graphics::red), this->charset));
	this->buttons.push(new Button("Quit", new Rectangle(50, 650, 4 * FONT_SIZE, 25, 0), this->charset));
	this->buttons.push(new Button("", new Rectangle(SCREEN_WIDTH/2 - 100 - 250, SCREEN_HEIGHT/2 - 75, 150, 150, Graphics::red), this->charset,this->numbers[0]));
	this->buttons.push(new Button("", new Rectangle(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 75, 150, 150, Graphics::red), this->charset,this->numbers[1]));
	this->buttons.push(new Button("", new Rectangle(SCREEN_WIDTH/2 - 100 + 250, SCREEN_HEIGHT/2 - 75, 150, 150, Graphics::red), this->charset,this->numbers[2]));
}

void GameController::loadGameState() {
	this->start();
}

void GameController::load(){
	switch (this->state) {
	case(MAIN_MENU):
		this->loadMainMenu();
		break;
	case(LEVEL_MENU):
		this->loadLevelMenu();
		break;
	case(GAME):
		this->loadGameState();
		break;
	default:
		this->mainMenu();
		break;
	}
}

void GameController::gameState() {
	char text[MAX_STRING];
	this->currentLevel->update(this->camera, this->delta);
	this->currentLevel->draw(this->camera);
	this->player->draw(this->screen, PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2);
	this->currentLevel->shoot(delta);

	//static drawing
	sprintf(text, "Elapsed time: = %.1lf s", this->worldTime);
	Graphics::String(this->screen, 800, 0, text, this->charset);

	//healthbar
	Graphics::Rectangle(this->screen, 30, 8, HEALTHBAR_WIDTH, 50, Graphics::gray, Graphics::gray);
	printf("\n%d\n", this->player->hp);
	Graphics::Rectangle(this->screen, 30, 10, HEALTHBAR_WIDTH * ((double)this->player->hp/ (double)PLAYER_HP), 49, Graphics::red, Graphics::red);
	Graphics::Surface(this->screen, this->healthBar, 0, 0,nullptr,false);
}

void GameController::start() {
	int playerX = SCREEN_WIDTH / 2;
	int playerY = SCREEN_HEIGHT / 2;

	delete this->currentLevel;
	delete this->player;
	delete this->camera;
	this->worldTime = 0;

	this->player = new Player(this->camera, new Rectangle(playerX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT, 0));
	this->camera = new Camera(this->player);

	char path[MAX_STRING] = {};
	sprintf(path,"./levels/%d/",this->levelNum);
	
	char tilesetPath[MAX_STRING] = {};
	sprintf(tilesetPath, "./levels/%d/tileset.bmp", this->levelNum);

	char basePath[MAX_STRING] = {};
	strcpy(basePath, path);

	Vector2 levelSize = Graphics::countCSV(strcat(basePath,"Base.csv"));

	this->currentLevel = new Level((int)levelSize.x, (int)levelSize.y, path, tilesetPath, this->screen, this->player, this->camera);
	this->player->setBulletsList(this->currentLevel->getPlayerBullets());
	this->currentLevel->init();
}

void GameController::update() {
	int t1 = SDL_GetTicks();
	int t2 = 0;
	int frameDelay = 1000 / MAX_FPS;

	int frameTime = 0;
	SDL_Rect r;
	//States state;
	//this->start();
	while (!this->quit) {
		this->mousePos.x = -100;
		this->mousePos.y = -100;
		this->eventHandler();

		t2 = SDL_GetTicks();
		this->delta = (t2 - t1) * 0.001;
		this->worldTime += this->delta;
		t1 = t2;
		SDL_FillRect(this->screen, NULL, 0);
		
		
		switch (this->state) {
		case(MAIN_MENU):
			this->mainMenu();
			break;
		case(LEVEL_MENU):
			this->levelMenu();
			break;
		case(GAME):
			this->gameState();
			break;
		default:
			this->mainMenu();
			break;
		}


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

		if(this->player != nullptr) this->player->controls(event);
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
		case (SDL_MOUSEBUTTONDOWN):
			int mouseX = 0;
			int mouseY = 0;
			SDL_GetMouseState(&mouseX, &mouseY);
			this->mousePos.x = mouseX;
			this->mousePos.y = mouseY;
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