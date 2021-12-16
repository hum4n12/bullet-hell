#pragma once
#include "./SDL2-2.0.10/include/SDL.h"
class Graphics{
public:
	// draw a text txt on surface screen, starting from the point (x, y) charset is a 128x128 bitmap containing character images
	static void String(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);

	// draw a surface sprite on a surface screen in point (x, y) | (x, y) is the center of sprite on screen
	static void Surface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y, SDL_Rect* srcRect = nullptr,bool centered = true);

	// draw a single pixel
	static void Pixel(SDL_Surface* surface, int x, int y, Uint32 color);

	// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
	static void Line(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);

	// draw a rectangle of size l by k
	static void Rectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

	//load image
	static void loadImage(const char* path, SDL_Surface* imageDest);

	//load csv
	static int* loadCSV(const char* path, int size);

};
