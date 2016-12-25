#pragma once
#include "SDL_Image.h"
#include "SDL.h"

class Texture
{
public:
	Texture();
	~Texture();

	/*
		Will load the texture as it is from a file
	*/
	bool loadImage(const char[]);

	SDL_Surface* getTexture();
	
	void drawTo(SDL_Surface*, int, int);

	int getWidth();
	void setWidth(int);

	int getHeight();
	void setHeight(int);

protected:
	SDL_Surface* texture;
	int width;
	int height;
};

