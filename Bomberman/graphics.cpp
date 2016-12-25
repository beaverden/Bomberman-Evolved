#include "graphics.h"



Graphics::Graphics()
{
}


Graphics::~Graphics()
{
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void Graphics::init(int height, int width)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow(
				"Bomberman Evolved",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				width,
				height,
				0
	);
	this->windowHeight = height;
	this->windowWidth = width;
	this->surface = SDL_GetWindowSurface(this->window);
}

void Graphics::setSurface(SDL_Surface * newSurface)
{
	this->surface = newSurface;
}

SDL_Surface * Graphics::getSurface()
{
	return this->surface;
}

void Graphics::fillRect(SDL_Rect * rect, Uint32 color)
{

	SDL_FillRect(this->surface, rect, color);
}

void Graphics::reset(Uint8 r, Uint8 g, Uint8 b)
{
	this->fillRect(NULL, this->getColor(r, g, b));
}

Uint32 Graphics::getColor(Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB(this->surface->format, r, g, b);
}


SDL_Rect * Graphics::getRect(int x, int y, int w, int h)
{
	SDL_Rect * rect = new SDL_Rect;
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return rect;
}

void Graphics::update()
{
	SDL_UpdateWindowSurface(this->window);
}

int Graphics::getHeight()
{
	return this->windowHeight;
}

int Graphics::getWidth()
{
	return this->windowWidth;
}
