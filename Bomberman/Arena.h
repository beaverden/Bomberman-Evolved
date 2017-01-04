#pragma once
#ifndef ARENA_H
#define ARENA_H

#include "DataStructures.h"
#include "AnimatedSprite.h"
#include "Globals.h"
#include "Bomb.h"


#define MAP_HEIGHT	Globals::BLOCKS_X
#define MAP_WIDTH	Globals::BLOCKS_Y
#define BLOCK_W		Globals::BLOCK_WIDTH
#define BLOCK_H     Globals::BLOCK_HEIGHT

class Arena
{
public:
	static void init();

	/*
		Generates unbreakable stone objects and randomly
		generates breakable walls, adds them to the respective vectors
	*/
	static void generateRandomArena();
	
	/*
		Creates a bomb and adds it to the bombs vector
		@param x position of the bomb
		@param y position of the bomb
		@param duration of the bomb preparation period
	*/
	static void placeBomb(int x, int y, int duration);


	/*
		Propagates the explosion of the specified bomb recursively in 
		all four direction and creates explosions in the reached places
		Destroys walls
		@param bomb to explode
	*/
	static void explodeBomb(Bomb bomb);
	static void explodeBomb(int x, int y, int dx, int dy, int step, int maxRadius);

	/*
		Creates a explosion and 
		@param x position of the explosion
		@param y position of the explosion
		@param type of the explosion (0 for up, 1 for right, 2 for down, 3 for left and 4 for the central position)
		@param whether the explosion is the last in the direction
	*/
	static void createExplosion(int x, int y, int type, bool last);

	/*
		Adds a random enemy to the arena in a free of other objects spot
	*/
	static void addEnemy();

	/*
		Updates explosions and bombs. Explodes the bombs if the itme is up and removes the object. 
		Removes the finished explosions
	*/
	static void update();

	/*
		Draws the grass, walls, stones, bombs and explosions
	*/
	static void drawArena();


private:
	static Sprite grassSprite;
	static Sprite wallSprite;
	static Sprite stoneSprite;

private:
	Arena() {}
};

#endif /* ARENA_H */
