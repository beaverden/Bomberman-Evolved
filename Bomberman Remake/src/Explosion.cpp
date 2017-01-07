#include "Explosion.h"

const float BLOCK_H = (float)Globals::BLOCK_HEIGHT;
const float BLOCK_W = (float)Globals::BLOCK_WIDTH;

Explosion::Explosion() {}

Explosion::Explosion(float posX, float posY, int type, bool last)
	: Object({ posX, posY, BLOCK_W, BLOCK_H })
{
	int closestMultipleX = (int)(posX / BLOCK_H);
	int closestMultipleY = (int)(posY / BLOCK_W);

	this->setObjectX(closestMultipleX * BLOCK_H);
	this->setObjectY(closestMultipleY * BLOCK_W);

	this->startedAt = std::clock();
	this->setAnimations(type, last);
}


Explosion::~Explosion() {}

AnimatedSprite& Explosion::getSprite()
{
	return this->sprite;
}

void Explosion::update()
{
	double percentage = (getElapsed() / (double)DEFAULT_EXPLOSION_DURATION);
	if (percentage < 0.25)
	{
		sprite.setAnimation("explode_1");
	}
	else if (percentage < 0.5)
	{
		sprite.setAnimation("explode_2");
	}
	else if (percentage < 0.75)
	{
		sprite.setAnimation("explode_3");
	}
	else
	{
		sprite.setAnimation("explode_4");
	}
}

bool Explosion::ended()
{
	return (getElapsed() > DEFAULT_EXPLOSION_DURATION);
}

Timestamp Explosion::getElapsed()
{
	return (std::clock() - startedAt);
}

void Explosion::setAnimations(int type, bool last)
{
	sprite.setTexture("resources/Images/explosions.png");
	int yPosition;
	if (type == 0 || type == 2) //up or down
	{
		yPosition = 32;
		if (last)
		{
			yPosition = (type == 0) ? 96 : 128;
		}
	}
	else if (type == 1 || type == 3)//left or right
	{
		yPosition = 64;
		if (last)
		{
			yPosition = (type == 1) ? 160 : 192;
		}
	}
	else if (type == 4)
	{
		yPosition = 0;
	}
	sprite.addAnimationFrame("explode_1", yPosition, 96, 32, 32);
	sprite.addAnimationFrame("explode_2", yPosition, 64, 32, 32);
	sprite.addAnimationFrame("explode_3", yPosition, 32, 32, 32);
	sprite.addAnimationFrame("explode_4", yPosition, 0,  32, 32);
	sprite.setAnimation("explode_1");
}