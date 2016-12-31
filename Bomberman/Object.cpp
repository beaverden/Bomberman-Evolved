#include "Object.h"



Object::Object() {}

Object::Object(SDL_Rect rect)
{
	this->boundingBox = rect;
}

Object::~Object() {}

int Object::getObjectX()
{
	return this->boundingBox.x;
}

int Object::getObjectY()
{
	return this->boundingBox.y;
}

int Object::getObjectW()
{
	return this->boundingBox.w;
}

int Object::getObjectH()
{
	return this->boundingBox.h;
}

SDL_Rect Object::getBox()
{
	return this->boundingBox;
}

void Object::setBox(SDL_Rect newBox)
{
	this->boundingBox = newBox;
}

bool Object::equals(SDL_Rect other)
{
	return (this->getObjectX() == other.x &&
			this->getObjectY() == other.y &&
			this->getObjectW() == other.w &&
			this->getObjectH() == other.h);
}

bool Object::collides(SDL_Rect other)
{
	
	int x1 = boundingBox.x;
	int y1 = boundingBox.y;
	int x2 = boundingBox.x + boundingBox.h;
	int y2 = boundingBox.y + boundingBox.w;

	int x3 = other.x;
	int y3 = other.y;
	int x4 = other.x + other.h;
	int y4 = other.y + other.w;

	return (in(x3, x1, x2) || in(x4, x1, x2)) &&
		   (in(y3, y1, y2) || in(y4, y1, y2));
	/*
	SDL_Rect rect = this->boundingBox;
	if (rect.x < other.x + other.w &&
		rect.x + rect.w > other.x &&
		rect.y < other.y + other.h &&
		rect.h + rect.y > other.y) {
		return true;
	}
	return false;
	*/
}


bool Object::in(int x1, int x2, int x3)
{
	return (x1 > x2 && x1 < x3);
}

bool Object::collides(Object other)
{
	return this->collides(other.getBox());
}

bool Object::collides(Vector <Object> objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (collides(objects[i])) return true;
	}
	return false;
}