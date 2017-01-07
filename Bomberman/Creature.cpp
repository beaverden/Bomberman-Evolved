#include "Creature.h"
#include <string>


Creature::Creature() 
{
	this->alive = true;
	this->hasMoved = false;
	this->diedAt = 0;
	this->movementDirection = 0;
	this->deathFrames = 0;
	this->movementSpeed = 0;
}

Creature::Creature(float x, float y, float movementSpeed, AnimatedSprite sprite)
{
	Creature();
	this->setObjectX(x);
	this->setObjectY(y);
	this->movementSpeed = movementSpeed;
	
	this->sprite = sprite;
}

Creature::~Creature() {}

void Creature::init()
{
	Creature();
}



void Creature::update(const ArenaObjects& objects)
{
	if (!alive && !canDraw()) return;
	if (!alive && canDraw())
	{
		deathAnimation();
		return;
	}

	for (int i = 0; i < objects.explosions.size(); i++)
	{
		if (objects.explosions[i].collides(this->getBox()))
		{
			this->setAlive(false);
			this->deathAnimation();
			break;
		}
	}
}


bool Creature::isAlive()
{
	return this->alive;
}

void Creature::setAlive(bool alive)
{
	if (alive == false)
	{
		this->diedAt = std::clock();
	}
	this->alive = alive;
}

void Creature::setDeathAnimationTime(int milliseconds)
{
	this->deathAnimationTime = milliseconds;
}