#include "Texture.h"
#include <stdio.h>


Texture::Texture()
{
}


Texture::~Texture()
{
	//SDL_FreeSurface(this->texture);
}

bool Texture::loadImage(const char filename[])
{
	if (filename)
	{
		this->texture = nullptr;
		this->texture = IMG_Load(filename);
		SDL_Rect rect = this->texture->clip_rect;
		if (texture)
		{
			this->width = rect.w;
			this->height = rect.h;
			return true;
		}
	}
	return false;
}

SDL_Surface* Texture::getTexture()
{
	return this->texture;
}

void Texture::drawTo(SDL_Surface* destination, int x, int y)
{
	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = width;
	position.h = height;
	SDL_BlitSurface(texture, nullptr, destination, &position);
}

int Texture::getWidth()
{
	return this->width;
}

void Texture::setWidth(int width)
{
	this->width = width;
}

int Texture::getHeight()
{
	return this->height;
}

void Texture::setHeight(int height)
{
	this->height = height;
}