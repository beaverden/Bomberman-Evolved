#include "Enemy.h"
#include "globals.h"


Enemy::Enemy()
{
}

Enemy::Enemy(int posX, int posY, int movementSpeed, AnimatedSprite sprite) :
	Creature(posX, posY, movementSpeed, sprite) {}

Enemy::~Enemy() {}

void Enemy::setupAnimations()
{
	this->setObjectH(Globals::BLOCK_HEIGHT);
	this->setObjectW(Globals::BLOCK_WIDTH);

	sprite.setTexture("Resources/sprites.png");
	sprite.addAnimationFrame("walk_down", 271, 93, 16, 16);
	sprite.addAnimationFrame("walk_down", 271, 122, 16, 16);
	sprite.addAnimationFrame("walk_down", 271, 152, 16, 16);

	sprite.addAnimationFrame("walk_left", 301, 93, 16, 16);
	sprite.addAnimationFrame("walk_left", 301, 122, 16, 16);

	sprite.addAnimationFrame("walk_up", 331, 93, 16, 16);
	sprite.addAnimationFrame("walk_up", 331, 122, 16, 16);

	sprite.addAnimationFrame("walk_right", 355, 93, 16, 16);
	sprite.addAnimationFrame("walk_right", 355, 122, 16, 16);

	sprite.addAnimationFrame("idle_down", 271, 93, 16, 16);
	sprite.addAnimationFrame("idle_left", 301, 93, 16, 16);
	sprite.addAnimationFrame("idle_up", 331, 93, 16, 16);
	sprite.addAnimationFrame("idle_right", 355, 93, 16, 16);
	sprite.addAnimationFrame("default", 271, 122, 16, 16);
	
	sprite.setAnimation("default");
}


void Enemy::makeMove()
{
	/*
	int dir = rand() % 4;
	switch (dir)
	{
	case 1: moveUp(); break;
	case 2: moveRight(); break;
	case 3: moveDown(); break;
	case 4: moveLeft(); break;
	}
	*/
	moveUp();
}