#pragma once
#ifndef ARENA_H
#define ARENA_H

#include "Object.h"
#include "Bomb.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Globals.h"
#include "Pair.h"
#include "Vector.h"
#include "AnimatedSprite.h"

//#include "Explosion.h"

#define MAP_HEIGHT	Globals::BLOCKS_X
#define MAP_WIDTH	Globals::BLOCKS_Y
#define BLOCK_W		Globals::BLOCK_WIDTH
#define BLOCK_H     Globals::BLOCK_HEIGHT

#define PII Pair<int, int> 
class Bomb;

class Arena
{
public:
	static void init();

	static void generateRandomArena();

	static void drawArena();

	static Vector <Object> stones; //Unbreakable objects
	static Vector <Object> walls;  //Breakable objects

	static Vector <Bomb> bombs;
	//static Vector <Explosion> explosions;

private:
	static Sprite grassSprite;
	static Sprite wallSprite;
	static Sprite stoneSprite;

private:
	Arena() {}
};

#endif /* ARENA_H */
