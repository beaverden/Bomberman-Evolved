#include "Creature.h"
#include "globals.h"
#include <string>

void Creature::setSprite(const std::string &filepath, SDL_Rect rect, int timeToUpdate)
{
	this->sprite.setTexture(filepath, rect);
	this->sprite.setTimeToUpdate(timeToUpdate);
}


AnimatedSprite& Creature::getSprite()
{
	return this->sprite;
}


void Creature::draw() 
{
	if (this->canDraw())
		sprite.draw(this->getObjectX(), this->getObjectY());
}


void Creature::draw(float x, float y)
{
	if (this->canDraw())
		sprite.draw(x, y);
}


void Creature::draw(float x, float y, float w, float h)
{
	if (this->canDraw())
		sprite.draw(x, y, w, h);
}


bool Creature::canDraw()
{
	if (!this->alive)
	{
		Timestamp elapsed = std::clock() - this->diedAt;
		if (elapsed >= this->deathAnimationTime)
			return false;
		else return true;
	}
	return true;
}


void Creature::deathAnimation()
{
	Timestamp elapsed = std::clock() - this->diedAt;
	double percentage = elapsed / (double)this->deathAnimationTime;
	for (int i = 1; i <= this->deathFrames; i++)
	{
		if (percentage <= i / (double)deathFrames)
		{
			std::string animationName = "die_" + std::to_string(i);
			sprite.setAnimation(animationName);
			break;
		}
	}
}


void Creature::setDeathFrames(int frames)
{
	this->deathFrames = frames;
}
