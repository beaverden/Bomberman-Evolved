#include "Player.h"
#include "ArenaObjects.h"

Player::Player() : Creature()
{
	this->lives = PLAYER_LIVES;
	this->alive = true;
	this->lastSetInvincible = 0;
}

Player::Player(float x, float y, float movementSpeed, AnimatedSprite sprite)
	: Creature(x, y, movementSpeed, sprite)
{
	Player();
}

Player::~Player() {}

int Player::getLives()
{
	return this->lives;
}

void Player::setLives(int newLives)
{
	this->lives = newLives;
}

void Player::decreaseLives()
{
	const int CURRENT_TIME_MS = SDL_GetTicks();
	if (CURRENT_TIME_MS - lastSetInvincible > PLAYER_INVINCIBLE_MS)
	{
		this->lives--;
		lastSetInvincible = CURRENT_TIME_MS;
	}
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
			if (this->lives > 0)
			{
				decreaseLives();
				return;
			}
			this->setAlive(false);
			this->deathAnimation();
			return;
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].collides(this->getBox()))
		{
			if (this->lives > 0)
			{
				decreaseLives();
				return;
			}
			this->setAlive(false);
			this->deathAnimation();
			return;
		}
	}
}