#include "Creature.h"
#include "ArenaObjects.h"

///Sets the object position though its setters
void Creature::setPosition(float x, float y)
{
	this->setObjectX(x);
	this->setObjectY(y);
}


void Creature::setSpeed(float speed)
{
	this->movementSpeed = speed;
}


///Verifies the movement in the specified direction
///by checking if it collides with any objects on the arena
bool Creature::canMove(float dx, float dy)
{
	ArenaObjects objects = ArenaObjects::getInstance();

	if (!this->isAlive()) return false;

	float x = this->getObjectX() + dx;
	float y = this->getObjectY() + dy;
	Box rect = this->getBox();
	rect.x = x;
	rect.y = y;
	for (int i = 0; i < objects.stones.size(); i++)
	{
		if (objects.stones[i].collides(rect)) return false;
	}
	for (int i = 0; i < objects.walls.size(); i++)
	{
		if (objects.walls[i].collides(rect)) return false;
	}
	return true;
}

///Sets the new position after moving in the [dx, dy] direction
void Creature::moveBy(float dx, float dy)
{
	this->setObjectX(this->getObjectX() + dx);
	this->setObjectY(this->getObjectY() + dy);
}


///Moves the player up, sets the direction and
///updates the variables related: hasMoved, movementDirection
void Creature::moveUp()
{
	float dx = -this->movementSpeed;
	float dy = 0;
	if (canMove(dx, dy))
	{
		moveBy(dx, dy);
		sprite.playAnimation("walk_up");
		this->hasMoved = true;
		this->movementDirection = 1;
	}
}


///Moves the player left, sets the direction and
///updates the variables related: hasMoved, movementDirection
void Creature::moveLeft()
{
	float dx = 0;
	float dy = -this->movementSpeed;
	if (canMove(dx, dy))
	{
		moveBy(dx, dy);
		sprite.playAnimation("walk_left");
		this->hasMoved = true;
		this->movementDirection = 2;
	}
}


///Moves the player down, sets the direction and
///updates the variables related: hasMoved, movementDirection
void Creature::moveDown()
{
	float dx = this->movementSpeed;
	float dy = 0;
	if (canMove(dx, dy))
	{
		moveBy(dx, dy);
		sprite.playAnimation("walk_down");
		this->hasMoved = true;
		this->movementDirection = 3;
	}
}


///Moves the player right, sets the direction and
///updates the variables related: hasMoved, movementDirection
void Creature::moveRight()
{
	float dx = 0;
	float dy = this->movementSpeed;
	if (canMove(dx, dy))
	{
		moveBy(dx, dy);
		sprite.playAnimation("walk_right");
		this->hasMoved = true;
		this->movementDirection = 4;
	}
}


///Depending on the direction sets player to idle
void Creature::idle()
{
	switch (this->movementDirection)
	{
	case 1: this->sprite.setAnimation("idle_up"); break;
	case 2: this->sprite.setAnimation("idle_left"); break;
	case 3: this->sprite.setAnimation("idle_down"); break;
	case 4: this->sprite.setAnimation("idle_right");  break;
	}
}


///Returns if the object has moved
///Resets the variable after the call
bool Creature::moved()
{
	bool moved = this->hasMoved;
	this->hasMoved = false;
	return moved;
}