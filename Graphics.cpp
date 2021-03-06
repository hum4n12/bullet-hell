#include "Graphics.h"
#include "GameController.h"
#include <stdio.h>
#include <stdlib.h>

void Graphics::String(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset,int fontSize){
	int px, py, c;
	SDL_Rect s, d;
	//SDL_Surface* a = SDL_CreateRGBSurface(SDL_SWSURFACE, 512, 512, charset->format->BitsPerPixel, charset->format->Rmask, charset->format->Gmask, charset->format->Bmask, charset->format->Amask);
	SDL_Surface* a = SDL_CreateRGBSurface(SDL_SWSURFACE, 256, 256, 32,0,0,0,0);
	SDL_Surface* b = SDL_CreateRGBSurface(SDL_SWSURFACE, fontSize*256/FONT_SIZE, fontSize * 256 / FONT_SIZE, 32,0,0,0,0);

	SDL_SetSurfaceBlendMode(a, SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(charset, SDL_BLENDMODE_NONE);
	SDL_BlitScaled(charset, NULL, a, NULL);
	SDL_BlitScaled(a, NULL, b, NULL);

	s.w = fontSize;
	s.h = fontSize;
	d.w = fontSize;
	d.h = fontSize;
	SDL_SetColorKey(charset, 1, 0);
	while (*text) {
		c = *text & 255;
		px = (c % 16) * fontSize;
		py = (c / 16) * fontSize;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(b, &s, screen, &d);
		x += fontSize;
		text++;
	};
	SDL_FreeSurface(a);
	SDL_FreeSurface(b);
};

void Graphics::Surface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y, SDL_Rect* srcRect,bool centered) {
	SDL_Rect dest;
	if (centered) {
		dest.x = x - sprite->w / 2;
		dest.y = y - sprite->h / 2;
	}
	else {
		dest.x = x;
		dest.y = y;
	}
	if (sprite == nullptr) {
		printf("\nerror");
		return;
	}
	if (srcRect == nullptr) {
		dest.w = sprite->w;
		dest.h = sprite->h;
	}
	else {
		dest.w = srcRect->w;
		dest.h = srcRect->h;
	}
	if(srcRect == nullptr)
		SDL_BlitSurface(sprite, NULL, screen, &dest);
	else
		SDL_BlitSurface(sprite, srcRect, screen, &dest);
};

// draw a single pixel
void Graphics::Pixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	if (x < 0 || x > SCREEN_WIDTH-1 || y < 0 || y > SCREEN_HEIGHT-1) return;
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

void Graphics::Line(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		Graphics::Pixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// draw a rectangle of size l by k
void Graphics::Rectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	Graphics::Line(screen, x, y, k, 0, 1, outlineColor);
	Graphics::Line(screen, x + l - 1, y, k, 0, 1, outlineColor);
	Graphics::Line(screen, x, y, l, 1, 0, outlineColor);
	Graphics::Line(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		Graphics::Line(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void Graphics::Circle(SDL_Surface* screen, int x, int y, int radius, Uint32 color, Uint32 colorBorder) {
	//horizontal
	for (int i = x - radius; i <= x + radius; i++) {
		//vertical
		for (int j = y - radius; j <= y + radius; j++) {
			double dist = pow((i - x), 2) + pow(j - y, 2);
			if (dist < pow(radius-6, 2)) {
				Graphics::Pixel(screen,i,j,color);
			}
			else if (dist <= pow(radius, 2)) {
				Graphics::Pixel(screen, i, j, colorBorder);
			}
		}
	}
}

void Graphics::drawHit(SDL_Surface* screen, int x, int y, int size){
	for (int i = x - size; i <= x + size; i++) {
		for (int j = y - size; j <= y + size; j++) {
			double dist = pow((i - x), 2) + pow(j - y, 2);
			if (j % 2 ==  0 && dist <= pow(size,2)) {
				Graphics::Pixel(screen, i, j, Graphics::darkRed);
			}
		}
	}
}


SDL_Surface* Graphics::loadImage(const char* path) {
	SDL_Surface* imageDest = SDL_LoadBMP(path);

	if (imageDest == nullptr) {
		printf("SDL_LoadBMP error: %s\n", SDL_GetError());
	};
	return imageDest;
}

int* Graphics::loadCSV(const char* path,int size) {
	int* data = new int[size];
	FILE* file;
	file = fopen(path, "r");
	char temp;
	int val = 0;
	int i = 0; //iterator
	temp = fgetc(file);

	while (!feof(file)) {
		if (temp == ',' || temp == 10 || temp == '\n') {
			data[i] = val;
			i++;
			val = 0;
		}
		else {
			val = (val*10)+(temp - '0');
		}
		temp = fgetc(file);
	}

	fclose(file);
	return data;
}

Vector2 Graphics::countCSV(const char* path) {
	Vector2 size = { 0,0 };

	FILE* file;
	file = fopen(path, "r");
	char temp;
	int i = 0; //iterator
	temp = fgetc(file);
	bool countColumns = true;

	while (!feof(file)) {
		if (temp == ','){ 
			if (countColumns) size.x++;
		}
		else if (temp == '\n' || temp == 10) {
			size.y++;
			countColumns = false;
		}
		temp = fgetc(file);
	}

	size.x++; // one ',' is missing
	fclose(file);

	return size;
}