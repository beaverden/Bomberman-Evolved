#include "Player.h"
#include "ArenaObjects.h"

Player::Player() : Creature() {}

Player::Player(float x, float y, float movementSpeed, AnimatedSprite sprite, int bombs = 0)
	: Creature(x, y, movementSpeed, sprite)
{
	this->bombs = bombs;
	this->alive = true;
}

Player::~Player()
{
}

int Player::getBombs()
{
	return this->bombs;
}

void Player::setBombs(int newBombs)
{
	this->bombs = newBombs;
}

void Player::update(const ArenaObjects& objects, 
				    const Vector <Enemy>& enemies)
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
			return;
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].collides(this->getBox()))
		{
			this->setAlive(false);
			this->deathAnimation();
			return;
		}
	}
}