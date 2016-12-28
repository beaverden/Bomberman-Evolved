#include "Sprite.h"


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

void Sprite::setRect(SDL_Rect newRect)
{
	this->usedRect = newRect;
}

void Sprite::draw(int y, int x)
{
	SDL_Rect destination = { x, y, usedRect.w, usedRect.h };
	Graphics::addToRenderer(texture, &usedRect, &destination);
}
