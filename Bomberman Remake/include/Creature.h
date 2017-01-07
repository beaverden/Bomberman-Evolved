#pragma once
#ifndef CREATURE_H
#define CREATURE_H

#include "AnimatedSprite.h"
#include "ArenaObjects.h"
#include "Object.h"
#include "SoundEffects.h"
#include <ctime>


// Functions that take care of drawing the creature
// Implemented in CreatureDrawing.cpp
/// setSprite()
/// getSprite()
/// canDraw()
/// draw()



// Functions that take care of creature movement and positioning
// Implemented in CreatureMovement.cpp
/// setSpeed()
/// setPosition()
/// canMove()
/// moveBy()
/// moveUp()
/// moveLeft()
/// moveDown()
/// moveRight()
/// idle()
/// moved()


typedef std::clock_t Timestamp;

class Creature: public Object
{
public:
	Creature();
	Creature(float posX, float posY, float movementSpeed, AnimatedSprite sprite);
	~Creature();

	void init();

	virtual void update(const ArenaObjects& objects);


	bool isAlive();
	void setAlive(bool);

	void setDeathAnimationTime(int milliseconds);

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
	bool canMove(float dx, float dy, const ArenaObjects& objects);
	

	/*
	Sets the new position after moving in the [dx, dy] direction
	@param dx (change in the x coordinate)
	@param dy (change in the y coordinate)
	*/
	void moveBy(float dx, float dy);

	void moveUp(const ArenaObjects& objects);
	void moveLeft(const ArenaObjects& objects);
	void moveDown(const ArenaObjects& objects);
	void moveRight(const ArenaObjects& objects);
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
	int deathAnimationTime;


};
#endif /* CREATURE_H */