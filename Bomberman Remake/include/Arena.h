#pragma once
#ifndef ARENA_H
#define ARENA_H

#include "AnimatedSprite.h"
#include "Globals.h"
#include "Bomb.h"
#include "Enemy.h"
#include "ArenaObjects.h"

#define MAP_HEIGHT	Globals::BLOCKS_X
#define MAP_WIDTH	Globals::BLOCKS_Y
#define BLOCK_W		Globals::BLOCK_WIDTH
#define BLOCK_H     Globals::BLOCK_HEIGHT


//Functions that create, place bombs: 
//Implemented in ArenaBombs.cpp
///	placeBomb();
///	explodeBomb();

//Function that generates and adds enemies: 
//Implemented in ArenaEnemies.cpp
/// addEnemy();

class Arena
{
public:
	Arena();
	~Arena();

	void init();

	void clear();

	void setup(int difficulty);

	/*
	Generates unbreakable stone objects and randomly
	generates breakable walls, adds them to the respective vectors
	*/
	void generateRandomArena();
	

	/*
	Creates a bomb and adds it to the bombs vector
	@param x position of the bomb
	@param y position of the bomb
	@param duration of the bomb preparation period
	*/
	void placeBomb(int x, int y, int duration);

	/*
	Adds a random enemy to the arena in a free of other objects spot
	*/
	void addEnemy();
	void addEnemies(int enemy);

	/*
	Updates explosions and bombs. Explodes the bombs if the itme is up and removes the object. 
	Removes the finished explosions
	*/
	void update();

	/*
	Draws the grass, walls, stones, bombs and explosions
	*/
	void drawArena();

	const ArenaObjects& getObjects();

	const Vector<Enemy>& getEnemies();

private:
	static Sprite grassSprite;
	static Sprite wallSprite;
	static Sprite stoneSprite;

	ArenaObjects objects;
	Vector <Enemy> enemies;
	float enemySpeed;

	/*
	Propagates the explosion of the specified bomb recursively in
	all four direction and creates explosions in the reached places
	Destroys walls
	@param bomb to explode
	*/
	void explodeBomb(Bomb bomb);
	void explodeBomb(int x, int y, int dx, int dy, int step, int maxRadius);


	/*
	Creates a explosion and
	@param x position of the explosion
	@param y position of the explosion
	@param type of the explosion (0 for up, 1 for right, 2 for down, 3 for left and 4 for the central position)
	@param whether the explosion is the last in the direction
	*/
	void createExplosion(int x, int y, int type, bool last);

	void setupEnemy(int posX, int posY);
};

#endif /* ARENA_H */
