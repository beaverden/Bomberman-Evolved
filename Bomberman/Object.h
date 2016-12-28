#pragma once
#include "SDL.h"
#include "Vector.h"
class Object
{
public:
	Object();
	Object(SDL_Rect rect);
	~Object();
	int getObjectX();
	int getObjectY();
	int getObjectW();
	int getObjectH();
	SDL_Rect getBox();

	void setBox(SDL_Rect newBox);

	bool collides(SDL_Rect other);
	bool collides(Object other);
	bool collides(Vector <Object> objects);
private:
	SDL_Rect boundingBox;

	/*
		Checks whether x1 is in (x2...x3)
		@param x1 number to be checked
		@param x2 interval start
		@param x3 interval end
	*/
	bool in(int x1, int x2, int x3);
};

