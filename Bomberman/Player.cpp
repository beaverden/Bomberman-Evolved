#include "Player.h"


Player::Player() : Creature() {}

Player::Player(float x, float y, int movementSpeed, AnimatedSprite sprite, int bombs = 0)
	: Creature(x, y, movementSpeed, sprite)
{
	this->bombs = bombs;
	this->alive = true;
}

Player::~Player()
{
}

int Player::getBombs()
{
	return this->bombs;
}

void Player::setBombs(int newBombs)
{
	this->bombs = newBombs;
}