#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include "graphics.h"

class Sprite
{
public:
	Sprite();
	Sprite(const std::string &filepath, SDL_Rect rect);
	Sprite(SDL_Texture* spriteSheet, SDL_Rect rect);
	~Sprite();
	
	void setTexture(SDL_Texture* texture, SDL_Rect rect);
	void setTexture(const std::string &filepath);
	void setTexture(const std::string &filepath, SDL_Rect rect);

	SDL_Texture* getTexture();

	void setRect(SDL_Rect rect);

	SDL_Rect getRect();

	/**
		Draw the sprite on the graphics screen
		Uses the given usedRect to get width and height
		@param x position of the sprite top-left corner
		@param y position of the sprite top-left corner
	*/
	void draw(float y, float x);
	void draw(float y, float x, float w, float h);

protected:
	SDL_Texture* texture;

	//The x,y,w,h parameters of the sprite on the texture;
	SDL_Rect usedRect;
private:
};

#endif /* SPRITE_H */