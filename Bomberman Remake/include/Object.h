#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "SDL.h"
#include "Vector.h"
#include "Box.h"

class Object
{
public:
	Object();
	Object(Box rect);
	~Object();

	float getObjectX();
	float getObjectY();
	float getObjectW();
	float getObjectH();

	void setObjectX(float x);
	void setObjectY(float y);
	void setObjectW(float w);
	void setObjectH(float h);

	Box getBox();

	void setBox(Box newBox);

	bool equals(Box other);

	/*
	Checks for collisions by calculating the common area of the two objects
	They collide if the common area is greater than zero
	*/
	bool collides(Box other);
	bool collides(Object other);
	bool collides(Vector <Object> objects);

protected:
	Box boundingBox;

	/*
		Checks whether x1 is in (x2...x3)
		@param x1 number to be checked
		@param x2 interval start
		@param x3 interval end
	*/
	bool in(float x1, float x2, float x3);
};


#endif /* OBJECT_H */

