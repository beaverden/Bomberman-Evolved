#pragma once
#ifndef CREATURE_H
#define CREATURE_H

#include "Object.h"
#include "AnimatedSprite.h"
#include "Arena.h"

class Creature: public Object
{
public:
	Creature();
	Creature(int posX, int posY, int movementSpeed, AnimatedSprite sprite);
	~Creature();


	/**
		@param x coordinate to move
		@param y coordinate to move
	*/
	void setPosition(int x, int y);


	/**
		@param dy difference to be added to Y coordinate
		@param dx difference to be added to X coordinate
	*/
	void moveBy(int dx, int dy);

	/**
		Checks if the creature can move in the given direction
		@param dx direction of movement
		@param dy direction of moment
		@param stones vector containing stone objects
		@param walls vector containing wall objects
	*/
	bool canMove(int dx, int dy);

	/**
		Sets the creature's sprite
		More information on the subroutine functions
		@param filepath on the machile (relative)
		@param rect to crop from the texture
	*/
	void setSprite(const std::string &filepath, SDL_Rect rect);


	AnimatedSprite& getSprite();


	/**
		Draws the creature to the window in its posX, posY
	*/
	void draw();
	void draw(int x, int y);

	int getPosX();
	int getPosY();

	bool isAlive();
	void setDead();

	void setSpeed(int speed);

	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();

	/**
		Checks if the player has moved in the previous frame
		Resets the hasMoved bool variable to false for each frame
		@return the current hasMoved value
	*/
	bool moved();

	/**
		Plays the idle animation in the last movement direction
	*/
	void idle();

private:
	int posX;
	int posY;
	int movementSpeed;
	bool alive;
	bool hasMoved;
	int movementDirection;
	AnimatedSprite sprite;
};

#endif /* CREATURE_H */