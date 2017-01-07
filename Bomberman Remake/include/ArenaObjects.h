#pragma once
#ifndef ARENA_OBJECTS_H
#define ARENA_OBJECTS_H

#include "Vector.h"
#include "Object.h"
#include "Bomb.h"
#include "Explosion.h"

class ArenaObjects
{
public:
	ArenaObjects();
	~ArenaObjects();

	Vector <Object> stones; //Unbreakable objects
	Vector <Object> walls;  //Breakable objects

	Vector <Bomb> bombs;
	Vector <Explosion> explosions;

};


#endif /* ARENA_OBJECTS_H */

