#pragma once
#ifndef ARENA_OBJECTS_H
#define ARENA_OBJECTS_H

#include "Vector.h"
#include "Object.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Enemy.h"

class ArenaObjects
{
public:
	static ArenaObjects& getInstance();

	//static Vector <Enemy> enemies

	static Vector <Object> stones; //Unbreakable objects
	static Vector <Object> walls;  //Breakable objects

	static Vector <Bomb> bombs;
	static Vector <Explosion> explosions;

	static Vector <Enemy> enemies;

private:
	ArenaObjects();
};


#endif /* ARENA_OBJECTS_H */

