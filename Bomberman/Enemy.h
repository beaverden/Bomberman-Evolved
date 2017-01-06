#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#pragma message("!!! Enemy IN")
#include "Creature.h"
#define ENEMY_SPEED 1.f
#define ENEMY_DEATH_TIME_MS 150
#define ENEMY_ANIMATION_UPDATE_MS 350

class Enemy : public Creature
{
public:
	Enemy();
	Enemy(float posX, float posY, float movementSpeed, AnimatedSprite sprite);
	~Enemy();

	void update(const ArenaObjects& objects);

	void setupAnimations();

	void makeMove(const ArenaObjects& objects);

private:
	int currentDirection;
	int lastDirection;

	int oppositeDirection(int direction);

	void move(int direction, const ArenaObjects& objects);
};
#pragma message("!!! Enemy OUT")
#endif /* ENEMY_H */

