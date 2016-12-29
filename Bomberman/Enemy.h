#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "Creature.h"

class Enemy : public Creature
{
public:
	Enemy();
	Enemy(int posX, int posY, int movementSpeed, AnimatedSprite sprite);
	~Enemy();

};

#endif /* ENEMY_H */

