#include "Arena.h"
#include "ArenaObjects.h"
#include "Pair.h"
#include "ArenaObjects.h"
#include <time.h>
#include <cstdlib>
#include <random>

Sprite Arena::grassSprite;
Sprite Arena::wallSprite;
Sprite Arena::stoneSprite;

#define BLOCK_H Globals::BLOCK_HEIGHT
#define BLOCK_W Globals::BLOCK_WIDTH

Arena::Arena() {}

Arena::~Arena() {}

void Arena::init()
{
	grassSprite.setTexture("Resources/grass.png");
	grassSprite.setRect({ 0, 0, Globals::BLOCK_WIDTH, Globals::BLOCK_HEIGHT });

	stoneSprite.setTexture("Resources/stone.png");
	stoneSprite.setRect({ 0, 0, Globals::BLOCK_WIDTH, Globals::BLOCK_HEIGHT });

	wallSprite.setTexture("Resources/wall.png");
	wallSprite.setRect({ 0, 0, Globals::BLOCK_WIDTH, Globals::BLOCK_HEIGHT });
}

void Arena::generateRandomArena()
{

	// -1 is a wall
	// -2 is a stone
	char mapObjects[MAP_HEIGHT][MAP_WIDTH] = { 0 };

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			Box rect = { 
				(float)i * BLOCK_W, 
				(float)j * BLOCK_H,
				(float)BLOCK_W,
				(float)BLOCK_H
			};
			//Walls
			if (i == 0 || j == 0 || i == MAP_HEIGHT - 1 || j == MAP_WIDTH - 1)
			{
				objects.stones.push_back(Object(rect));
				mapObjects[i][j] = -1;
			}
			else if (i % 2 == 0 && j % 2 == 0 &&
					 i > 1 && i < MAP_HEIGHT - 2 &&
					 j > 1 && j < MAP_WIDTH  - 2)
			{
				objects.stones.push_back(Object(rect));
				mapObjects[i][j] = -1;
			}
		}
	}

	for (int i = 0; i < Globals::RANDOM_BLOCKS; i++)
	{
		int rx = 1 + rand() % (MAP_WIDTH  - 2),
			ry = 1 + rand() % (MAP_HEIGHT - 2);
		if (mapObjects[rx][ry] == 0)
		{
			objects.walls.push_back(
				Object({ 
					(float)rx * BLOCK_W, 
					(float)ry * BLOCK_H,
					(float)BLOCK_W,
					(float)BLOCK_H
				})
			);
			mapObjects[rx][ry] = -2;
		}	
	}
}


void Arena::createExplosion(int x, int y, int type, bool last)
{
	objects.explosions.push_back(
		Explosion(x, y, type, last)
	);
}



void Arena::update()
{

	for (int i = 0; i < objects.bombs.size(); i++)
	{
		if (objects.bombs[i].exploded())
		{
			explodeBomb(objects.bombs[i]);
			objects.bombs.remove(i);
		}
		else
		{
			objects.bombs[i].update();
		}
	}

	for (int i = 0; i < objects.explosions.size(); i++)
	{
		if (objects.explosions[i].ended())
		{
			objects.explosions.remove(i);
		}
		else
		{
			objects.explosions[i].update();
		}
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i].canDraw())
		{
			enemies.remove(i);
		}
		else
		{
			enemies[i].makeMove(objects);
			enemies[i].update(objects);
		}
		
	}
}

void Arena::drawArena()
{
	for (int i = 0; i < Globals::ARENA_HEIGHT; i += 30)
	{
		for (int j = 0; j < Globals::ARENA_WIDTH; j += 30)
		{
			grassSprite.draw(i, j);
		}
	}
	for (int i = 0; i < objects.stones.size(); i++)
	{
		Box rect = objects.stones[i].getBox();
		stoneSprite.draw(rect.x, rect.y);
	}


	for (int i = 0; i < objects.walls.size(); i++)
	{
		Box rect = objects.walls[i].getBox();
		wallSprite.draw(rect.x, rect.y);
	}

	for (int i = 0; i < objects.bombs.size(); i++)
	{
		objects.bombs[i].getSprite().draw(
			objects.bombs[i].getPosX(),
			objects.bombs[i].getPosY()
		);
	}
	for (int i = 0; i < objects.explosions.size(); i++)
	{
		objects.explosions[i].getSprite().draw(
			objects.explosions[i].getObjectX(),
			objects.explosions[i].getObjectY()
		);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].draw(
			enemies[i].getObjectX(),
			enemies[i].getObjectY(),
			enemies[i].getObjectW(),
			enemies[i].getObjectH()
		);
	}
}

const ArenaObjects& Arena::getObjects()
{
	return this->objects;
}

const Vector<Enemy> & Arena::getEnemies()
{
	return this->enemies;
}