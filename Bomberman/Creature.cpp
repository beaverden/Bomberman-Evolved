#include "Creature.h"



Creature::Creature()
{
}

Creature::Creature(int x, int y, int movementSpeed, AnimatedSprite sprite)
{
	this->posX = x;
	this->posY = y;
	this->movementSpeed = movementSpeed;
	this->alive = true;
	this->hasMoved = false;
	this->movementDirection = 0;
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

bool Creature::canMove(int dx, int dy)
{
	int x = posX + dx;
	int y = posY + dy;
	//printf("%d %d\n", x, y);
	SDL_Rect rect = this->getBox();
	rect.x = x;
	rect.y = y;
	for (int i = 0; i < Arena::stones.size(); i++)
	{
		if (Arena::stones[i].collides(rect)) return false;
	}
	for (int i = 0; i < Arena::walls.size(); i++)
	{
		if (Arena::walls[i].collides(rect)) return false;
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

void Creature::setSpeed(int speed)
{
	this->movementSpeed = speed;
}

bool Creature::moveLeft()
{
	int dx = 0;
	int dy = -this->movementSpeed;
	if (canMove(dx, dy))
	{
		moveBy(dx, dy);
		sprite.playAnimation("walk_left");
		this->hasMoved = true;
		this->movementDirection = 1;
		return true;
	}
	return false;
}

bool Creature::moveRight()
{
	int dx = 0;
	int dy = this->movementSpeed;
	if (canMove(dx, dy))
	{
		moveBy(dx, dy);
		sprite.playAnimation("walk_right");
		this->hasMoved = true;
		this->movementDirection = 2;
		return true;
	}
	return false;
}

bool Creature::moveUp()
{
	int dx = -this->movementSpeed;
	int dy = 0;
	if (canMove(dx, dy))
	{
		moveBy(dx, dy);
		sprite.playAnimation("walk_up");
		this->hasMoved = true;
		this->movementDirection = 3;
		return true;
	}
	return false;
}

bool Creature::moveDown()
{
	int dx = this->movementSpeed;
	int dy = 0;
	if (canMove(dx, dy))
	{
		moveBy(dx, dy);
		sprite.playAnimation("walk_down");
		this->hasMoved = true;
		this->movementDirection = 4;
		return true;
	}
	return false;
}

bool Creature::moved()
{
	bool moved = this->hasMoved;
	this->hasMoved = false;
	return moved;
}

void Creature::idle()
{

	switch (this->movementDirection)
	{
	case 1: this->sprite.playAnimation("idle_left"); break;
	case 2: this->sprite.playAnimation("idle_right"); break;
	case 3: this->sprite.playAnimation("idle_up"); break;
	case 4: this->sprite.playAnimation("idle_down"); break;
	}
}