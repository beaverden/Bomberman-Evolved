#include "Box.h"
#include <math.h>

#define EPSILON 1e-3


Box::Box() {}

Box::Box(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Box::~Box() {}

Box Box::operator()(float x, float y, float w, float h)
{
	Box box(x, y, w, h);
	return box;
}

bool Box::operator==(const Box& other)
{
	return (fabs(this->x - other.x) < EPSILON &&
			fabs(this->y - other.y) < EPSILON &&
			fabs(this->w - other.w) < EPSILON &&
			fabs(this->h - other.h) < EPSILON);
}

bool Box::operator!=(const Box& other)
{
	return !(*this == other);
}