#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

class Player : public Creature
{
public:
	Player();
	Player(float x, float y, int movementSpeed, AnimatedSprite sprite, int bombs);
	~Player();

	int getBombs();

	void setBombs(int newBombs);

private:
	int posX;
	int posY;
	int bombs;
};

#endif /* PLAYER_H */

