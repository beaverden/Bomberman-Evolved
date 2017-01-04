#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"

class Enemy : public Creature
{
public:
	Enemy();
	Enemy(int posX, int posY, int movementSpeed, AnimatedSprite sprite);
	~Enemy();

	void setupAnimations();

	void makeMove();
};

#endif /* ENEMY_H */

