#pragma once
#ifndef CREATURE_H
#define CREATURE_H
#include "AnimatedSprite.h"
#include "Object.h"
#include <ctime>

typedef std::clock_t Timestamp;

class Creature: public Object
{
public:
	Creature();
	Creature(float posX, float posY, float movementSpeed, AnimatedSprite sprite);
	~Creature();

	void init();

	void update();


	bool isAlive();
	void setAlive(bool);


	/*
	Implemented in CreatureDrawing.cpp
	Declares the function related to drawing the creature to the screen
	setSprite()
	getSprite()
	canDraw()
	draw()
	*/

	/*
	Sets the creature's sprite
	@see Sprite::setTexture()
	@param filepath on the machile (relative)
	@param rect to crop from the texture
	@param timeToUpdate of the sprite
	*/
	void setSprite(const std::string &filepath, SDL_Rect rect, int timeToUpdate);

	AnimatedSprite& getSprite();

	void draw();
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);
	bool canDraw();
	void deathAnimation();
	void setDeathFrames(int frames);


	/*
	Implemented in CreatureMovement.cpp
	Declares all the positioning related functions
	setSpeed()
	setPosition()
	canMove()
	moveBy()
	moveUp()
	moveLeft()
	moveDown()
	moveRight()
	idle()
	moved()
	*/


	/* 
	Sets the object position though its setters
	@param x coordinate of the object
	@param y coordinate of the object 
	*/
	void setPosition(float x, float y);

	/*
	Sets the speed
	@param speed of the object
	*/
	void setSpeed(float speed);

	/* 
	Verifies the movement in the specified direction
	by checking if it collides with any objects on the arena
	@param dx (change in the x coordinate)
	@param dy (change in the y coordinate)
	*/
	bool canMove(float dx, float dy);
	

	/*
	Sets the new position after moving in the [dx, dy] direction
	@param dx (change in the x coordinate)
	@param dy (change in the y coordinate)
	*/
	void moveBy(float dx, float dy);

	void moveUp();
	void moveLeft();
	void moveDown();
	void moveRight();
	void idle();

	bool moved();

protected:
	float movementSpeed;

	bool alive;
	bool hasMoved;
	int movementDirection;
	AnimatedSprite sprite;

	Timestamp diedAt;
	int deathFrames;


};

#endif /* CREATURE_H */