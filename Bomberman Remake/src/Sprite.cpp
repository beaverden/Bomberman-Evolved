#include "Sprite.h"
#include <math.h>

Sprite::Sprite() {}

Sprite::Sprite(const std::string &filepath, SDL_Rect rect)
{
	this->texture = Graphics::loadTexture(filepath);
	this->usedRect = rect;
}

Sprite::Sprite(SDL_Texture* spriteSheet, SDL_Rect rect)
{
	this->texture = spriteSheet;
	this->usedRect = rect;
}

Sprite::~Sprite() {}

void Sprite::setTexture(SDL_Texture* texture, SDL_Rect rect)
{
	this->texture = texture;
	this->usedRect = rect;
}

void Sprite::setTexture(const std::string &filepath)
{
	this->texture = Graphics::loadTexture(filepath);
}

void Sprite::setTexture(const std::string &filepath, SDL_Rect rect)
{
	this->texture = Graphics::loadTexture(filepath);
	this->usedRect = rect;
}

SDL_Texture* Sprite::getTexture()
{
	return this->texture;
}

void Sprite::setRect(SDL_Rect newRect)
{
	this->usedRect = newRect;
}

SDL_Rect Sprite::getRect()
{
	return this->usedRect;
}

void Sprite::draw(float y, float x)
{
	int intY = (int)roundf(y);
	int intX = (int)roundf(x);

	SDL_Rect destination = { intX, intY, usedRect.w, usedRect.h };
	Graphics::addToRenderer(texture, &usedRect, &destination);
}

void Sprite::draw(float y, float x, float w, float h)
{
	int intY = (int)roundf(y);
	int intX = (int)roundf(x);
	int intW = (int)roundf(w);
	int intH = (int)roundf(h);

	SDL_Rect destination = { intX, intY, intW, intH };
	Graphics::addToRenderer(texture, &usedRect, &destination);
}
