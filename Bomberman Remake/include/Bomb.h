#pragma once
#ifndef BOMB_H
#define BOMB_H

#include "Object.h"
#include "AnimatedSprite.h"
#include <ctime>

#define BOMB_HEIGHT 17
#define BOMB_WIDTH 17

typedef std::clock_t Timestamp;

class Bomb : public Object
{
public:
	Bomb();
	Bomb(int x, int y, int duration, int explosionRadius = 3);
	~Bomb();

	Timestamp getPlacedTime();
	int getBombTime();

	void setBombTime(int duration);
	void setExplosionArea(int area);

	void update();

	bool exploded();

	int getPosX();
	int getPosY();
	int getExplosionRadius();
	AnimatedSprite& getSprite();

private:
	AnimatedSprite sprite;
	Timestamp placedAt;
	int bombTime;
	int explosionRadius;

	int bombPosX;
	int bombPosY;

	void setAnimations();

	Timestamp getElapsed();

	/*
		Places the bomb at the block that is actually in the place
		Where 3/10 of the player height and 5/10 of the player width point lies
		@param x position of the player
		@param y position of the player
		@return Pair<x position of the block, y position of the block>
	*/
	Pair<int, int> getPlacementPosition(int x, int y);
};

#endif /* BOMB_H */

