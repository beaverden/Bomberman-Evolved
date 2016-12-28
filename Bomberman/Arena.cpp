#include <time.h>
#include <random>
#include "Arena.h"
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"
#include <limits.h>
#include "Pair.h"

Sprite Arena::grassSprite;
Sprite Arena::wallSprite;
Sprite Arena::stoneSprite;

Vector <Object> Arena::stones;
Vector <Object> Arena::walls;

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
	srand(time(0));
	char arr[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			SDL_Rect rect = { i * BLOCK_W, j * BLOCK_H, BLOCK_W, BLOCK_H };
			//Walls
			if (i == 0 || j == 0 || i == MAP_HEIGHT - 1 || j == MAP_WIDTH - 1)
			{
				stones.push_back(Object(rect));
				arr[i][j] = -1;
			}
			else if (i % 2 == 0 && j % 2 == 0 &&
					 i > 1 && i < MAP_HEIGHT - 2 &&
					 j > 1 && j < MAP_WIDTH  - 2)
			{
				stones.push_back(Object(rect));
				arr[i][j] = -1;
			}
		}
	}

	for (int i = 0; i < Globals::RANDOM_BLOCKS; i++)
	{
		int rx = 1 + rand() % (MAP_WIDTH  - 2),
			ry = 1 + rand() % (MAP_HEIGHT - 2);
		if (arr[rx][ry] == 0)
		{
			walls.push_back(Object({ rx * BLOCK_W, ry * BLOCK_H, BLOCK_W, BLOCK_H }));
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
	for (int i = 0; i < stones.size(); i++)
	{
		SDL_Rect rect = stones[i].getBox();
		stoneSprite.draw(rect.x, rect.y);
	}


	for (int i = 0; i < walls.size(); i++)
	{
		SDL_Rect rect = walls[i].getBox();
		wallSprite.draw(rect.x, rect.y);
	}
}