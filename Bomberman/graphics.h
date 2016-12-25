#pragma once
#include "SDL.h"
class Graphics
{
public:
	Graphics();
	~Graphics();

	void init(int, int);

	void setSurface(SDL_Surface *);

	SDL_Surface * getSurface();

	void fillRect(SDL_Rect *, Uint32);

	void reset(Uint8, Uint8, Uint8);

	Uint32 getColor(Uint8, Uint8, Uint8);

	SDL_Rect * getRect(int, int, int, int);

	void update();

	int getHeight();

	int getWidth();

private:
	int windowHeight;
	int windowWidth;
	SDL_Window * window;
	SDL_Surface * surface;
};

