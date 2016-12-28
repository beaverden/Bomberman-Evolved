#pragma once
#include "Object.h"
#include "AnimatedSprite.h"

class Creature: public Object
{
public:
	Creature();
	Creature(int posX, int posY, AnimatedSprite sprite);
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
	bool canMove(int dx, int dy, Vector <Object> &stones, Vector<Object> &walls);

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

private:
	int posX;
	int posY;
	int movementSpeed;
	bool alive;
	AnimatedSprite sprite;
};

