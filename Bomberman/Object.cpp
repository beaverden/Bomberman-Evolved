#include "Object.h"
#include <algorithm>


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
	
	float x1 = boundingBox.x;
	float y1 = boundingBox.y;
	float x2 = boundingBox.x + boundingBox.h;
	float y2 = boundingBox.y + boundingBox.w;

	float x3 = other.x;
	float y3 = other.y;
	float x4 = other.x + other.h;
	float y4 = other.y + other.w;

	float commonX1 = std::max(x1, x3);
	float commonX2 = std::min(x2, x4);
	float commonY1 = std::max(y1, y3);
	float commonY2 = std::min(y2, y4);

	if (commonX2 - commonX1 > 0 && commonY2 - commonY1 > 0)
	{
		float area = (commonX2 - commonX1) * (commonY2 - commonY1);
		if (area > 0) return true;
	}
	return false;

	//return (in(x3, x1, x2) || in(x4, x1, x2)) &&
	//	   (in(y3, y1, y2) || in(y4, y1, y2));
}


bool Object::in(float x1, float x2, float x3)
{
	return (x1 >= x2 && x1 <= x3);
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