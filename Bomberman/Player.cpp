#include "Player.h"


Player::Player() : Creature() {}

Player::Player(int x, int y, AnimatedSprite sprite, int bombs = 0) 
	: Creature(x, y, sprite)
{
	this->bombs = bombs;
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