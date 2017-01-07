#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Enemy.h"
#define PLAYER_DEATH_ANIMATION_TIME 500;
#define PLAYER_LIVES 3
#define PLAYER_INVINCIBLE_MS 2000

class Player : public Creature
{
public:
	Player();
	Player(float x, float y, float movementSpeed, AnimatedSprite sprite);
	~Player();

	int getLives();

	void setLives(int newLives);

	void decreaseLives();

	/*
	Overriden virtual function from Creature
	Also checks for collisions with enemies
	*/
	void update(const ArenaObjects& objects,
		        const Vector <Enemy>& enemies);

private:
	int posX;
	int posY;
	int lives;
	int lastSetInvincible;
};

#endif /* PLAYER_H */

