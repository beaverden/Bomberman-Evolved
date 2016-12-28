#pragma once
#include "Creature.h"

class Player : public Creature
{
public:
	Player();
	Player(int x, int y, AnimatedSprite sprite, int bombs);
	~Player();

	int getBombs();

	void setBombs(int newBombs);

private:
	int posX;
	int posY;
	int bombs;
};

