#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(int posX, int posY, int movementSpeed, AnimatedSprite sprite) :
	Creature(posX, posY, movementSpeed, sprite) {}

Enemy::~Enemy()
{
}
