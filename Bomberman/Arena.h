#pragma once
#include "LinkedList.h"
#include "Stack.h"
#include "Globals.h"
#include "Pair.h"
#include "Vector.h"
#include "Object.h"
#include "AnimatedSprite.h"

#define MAP_HEIGHT	Globals::BLOCKS_X
#define MAP_WIDTH	Globals::BLOCKS_Y
#define BLOCK_W		Globals::BLOCK_WIDTH
#define BLOCK_H     Globals::BLOCK_HEIGHT

#define PII Pair<int, int> 

class Arena
{
public:
	static void init();

	static void generateRandomArena();

	static void drawArena();

	static Vector <Object> stones;
	static Vector <Object> walls;

private:
	static Sprite grassSprite;
	static Sprite wallSprite;
	static Sprite stoneSprite;

private:
	Arena() {}
};
