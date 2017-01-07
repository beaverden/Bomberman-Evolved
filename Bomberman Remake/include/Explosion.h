#pragma once
#include <ctime>
#include "AnimatedSprite.h"
#include "Object.h"
#include "globals.h"

#define DEFAULT_EXPLOSION_DURATION Globals::DEFAULT_EXPLOSION_DURATION
typedef std::clock_t Timestamp;

class Explosion: public Object
{
public:
	Explosion();

	/*
	Creates a explosion at normated (to block size) coordinates
	Needs a specified type (vertical, horizontal)
	And if is the last explosion in the direction
	@param posX of the explosion
	@param posY of the explosion
	@param dir (0 for up, 1 for right, 2 for down, 3 for left, 4 for central explosion)
	@param last (true if it is the last in its direction)
	*/
	Explosion(float posX, float posY, int type, bool last);
	~Explosion();

	AnimatedSprite& getSprite();

	void update();

	/*
	@return The time of the explosion animation is up
	*/
	bool ended();

private:
	AnimatedSprite sprite;
	Timestamp startedAt;

	void setAnimations(int type, bool last);

	Timestamp getElapsed();
};

