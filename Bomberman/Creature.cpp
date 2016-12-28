#include "Creature.h"



Creature::Creature()
{
}

Creature::Creature(int x, int y, AnimatedSprite sprite)
{
	this->posX = x;
	this->posY = y;
	this->alive = true;
	this->sprite = sprite;
}

Creature::~Creature()
{
}

void Creature::setPosition(int x, int y)
{
	this->posX = x;
	this->posY = y;

}

void Creature::moveBy(int dx, int dy)
{
	this->posX += dx;
	this->posY += dy;
	printf("%d %d\n", posX, posY);
}

bool Creature::canMove(int dx, int dy, Vector <Object> &stones, Vector<Object> &walls)
{
	int x = posX + dx;
	int y = posY + dy;
	//printf("%d %d\n", x, y);
	SDL_Rect rect = this->getBox();
	rect.x = x;
	rect.y = y;
	for (int i = 0; i < stones.size(); i++)
	{
		if (stones[i].collides(rect)) return false;
	}
	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i].collides(rect)) return false;
	}
	return true;
}

void Creature::setSprite(const std::string &filepath, SDL_Rect rect)
{
	this->sprite.setTexture(filepath, rect);
}

AnimatedSprite& Creature::getSprite()
{
	return this->sprite;
}


void Creature::draw()
{
	sprite.draw(this->posX, this->posY);
}

void Creature::draw(int x, int y)
{
	sprite.draw(x, y);
}

int Creature::getPosX()
{
	return this->posX;
}

int Creature::getPosY()
{
	return this->posY;
}

bool Creature::isAlive()
{
	return this->alive;
}

void Creature::setDead()
{
	this->alive = false;
}