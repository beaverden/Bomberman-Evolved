#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Enemy.h"
#define PLAYER_DEATH_ANIMATION_TIME 500;

class Player : public Creature
{
public:
	Player();
	Player(float x, float y, float movementSpeed, AnimatedSprite sprite, int bombs);
	~Player();

	int getBombs();

	void setBombs(int newBombs);

	/*
	Overriden virtual function from Creature
	Also checks for collisions with enemies
	*/
	void update(const ArenaObjects& objects,
		        const Vector <Enemy>& enemies);

private:
	int posX;
	int posY;
	int bombs;
};

#endif /* PLAYER_H */

