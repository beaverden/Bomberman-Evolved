#include "Enemy.h"
#include "globals.h"
#include "ArenaObjects.h"

Enemy::Enemy()
{
	this->currentDirection = 0;
	this->lastDirection = 0;
}

Enemy::Enemy(float posX, float posY, float movementSpeed, AnimatedSprite sprite) :
	Creature(posX, posY, movementSpeed, sprite) 
{
	Enemy();
}

Enemy::~Enemy() {}

void Enemy::setupAnimations()
{
	this->setObjectH(Globals::BLOCK_HEIGHT);
	this->setObjectW(Globals::BLOCK_WIDTH);

	sprite.setTexture("resources/Images/sprites.png");
	sprite.addAnimationFrame("walk_down", 271, 123, 16, 16);
	sprite.addAnimationFrame("walk_down", 271, 153, 16, 16);

	sprite.addAnimationFrame("walk_left", 301, 93, 16, 16);
	sprite.addAnimationFrame("walk_left", 301, 123, 16, 16);

	sprite.addAnimationFrame("walk_up", 331, 153, 16, 16);
	sprite.addAnimationFrame("walk_up", 331, 123, 16, 16);

	sprite.addAnimationFrame("walk_right", 355, 93, 16, 16);
	sprite.addAnimationFrame("walk_right", 355, 123, 16, 16);

	sprite.addAnimationFrame("idle_down", 271, 93, 16, 16);
	sprite.addAnimationFrame("idle_left", 301, 93, 16, 16);
	sprite.addAnimationFrame("idle_up", 331, 93, 16, 16);
	sprite.addAnimationFrame("idle_right", 355, 93, 16, 16);

	sprite.addAnimationFrame("default", 271, 123, 16, 16);
	
	sprite.setAnimation("default");
}

int Enemy::oppositeDirection(int direction)
{
	if (direction == 2) return 4;
	else return (direction + 2) % 4;
}

void Enemy::makeMove(const ArenaObjects& objects)
{
	//Check disponible directions
	int dx[] = { -1, 0, 1, 0 },
		dy[] = { 0, 1, 0, -1 };
	Vector <int> directions;
	for (int i = 0; i < 4; i++)
	{
		float directionX = dx[i] * this->movementSpeed;
		float directionY = dy[i] * this->movementSpeed;
		if (this->canMove(directionX, directionY, objects))
		{
			//1 for up, ... , 4 for left
			int directionToTake = i + 1;
			if (directionToTake != oppositeDirection(currentDirection))
			{
				directions.push_back(i + 1);
			}	
		}
	}
	if (directions.size() == 0)
	{
		move(oppositeDirection(this->currentDirection), objects);
		return;
	}
	int randomDirectionIndex = rand() % directions.size();
	move(directions[randomDirectionIndex], objects);
}

void Enemy::move(int direction, const ArenaObjects& objects)
{
	this->currentDirection = direction;
	switch (direction)
	{
	case 1: moveUp(objects); break;
	case 2: moveRight(objects); break;
	case 3: moveDown(objects); break;
	case 4: moveLeft(objects); break;
	}
}

void Enemy::update(const ArenaObjects& objects)
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
			SoundEffects::playEffect("Happy");
			this->setAlive(false);
			this->deathAnimation();
			break;
		}
	}
}