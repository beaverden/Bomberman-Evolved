#include "Object.h"



Object::Object() {}

Object::Object(Box rect)
{
	this->boundingBox = rect;
}

Object::~Object() {}

float Object::getObjectX()
{
	return this->boundingBox.x;
}

float Object::getObjectY()
{
	return this->boundingBox.y;
}

float Object::getObjectW()
{
	return this->boundingBox.w;
}

float Object::getObjectH()
{
	return this->boundingBox.h;
}

void Object::setObjectX(float x)
{
	this->boundingBox.x = x;
}

void Object::setObjectY(float y)
{
	this->boundingBox.y = y;
}

void Object::setObjectW(float w)
{
	this->boundingBox.w = w;
}

void Object::setObjectH(float h)
{
	this->boundingBox.h = h;
}

Box Object::getBox()
{
	return this->boundingBox;
}

void Object::setBox(Box newBox)
{
	this->boundingBox = newBox;
}

bool Object::equals(Box other)
{
	return (this->boundingBox == other);
}

bool Object::collides(Box other)
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
}


bool Object::in(float x1, float x2, float x3)
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