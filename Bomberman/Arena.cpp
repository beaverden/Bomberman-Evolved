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
	ArenaObjects objects = ArenaObjects::getInstance();

	char arr[MAP_HEIGHT][MAP_WIDTH] = { 0 };
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
				arr[i][j] = -1;
			}
			else if (i % 2 == 0 && j % 2 == 0 &&
					 i > 1 && i < MAP_HEIGHT - 2 &&
					 j > 1 && j < MAP_WIDTH  - 2)
			{
				objects.stones.push_back(Object(rect));
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
			objects.walls.push_back(
				Object({ 
					(float)rx * BLOCK_W, 
					(float)ry * BLOCK_H,
					(float)BLOCK_W,
					(float)BLOCK_H
				})
			);
			arr[rx][ry] = -2;
		}	
	}
}

void Arena::placeBomb(int x, int y, int duration)
{
	ArenaObjects::getInstance().bombs.push_back(Bomb(x, y, duration));
}

void Arena::explodeBomb(Bomb bomb)
{
	int blockX = bomb.getPosX() - bomb.getPosX() % BLOCK_H;
	int blockY = bomb.getPosY() - bomb.getPosY() % BLOCK_W;

	createExplosion(blockX, blockY, 4, false);
	explodeBomb(blockX, blockY, -BLOCK_H, 0, 0, bomb.getExplosionRadius());
	explodeBomb(blockX, blockY, 0, -BLOCK_W, 0, bomb.getExplosionRadius());
	explodeBomb(blockX, blockY, 0, BLOCK_W, 0, bomb.getExplosionRadius());
	explodeBomb(blockX, blockY, BLOCK_H, 0, 0, bomb.getExplosionRadius());
}

void Arena::explodeBomb(int x, int y, int dx, int dy, int step, int maxRadius)
{

	Box rect = {
		(float)x,
		(float)y,
		(float)BLOCK_W,
		(float)BLOCK_H
	};
	ArenaObjects objects = ArenaObjects::getInstance();

	for (int i = 0; i < objects.stones.size(); i++)
	{
		//Exits if encountered a stone
		if (objects.stones[i].equals(rect)) return;
	}

	bool foundWall = false;
	for (int i = 0; i < objects.walls.size(); i++)
	{
		if (objects.walls[i].equals(rect))
		{
			objects.walls.remove(i);
			foundWall = true;
			break;
		}
	}

	bool isLast = (step + 1 == maxRadius);
	if (foundWall) isLast = true;
	//Explosion was already placed in the center
	//If the step is 0, then it checks the center position
	if (step != 0)
	{
		//Create explosion
		if (dx < 0 && dy == 0) // up
			Arena::createExplosion(x, y, 0, isLast);
		if (dx == 0 && dy > 0) // right
			Arena::createExplosion(x, y, 1, isLast);
		if (dx > 0 && dy == 0) // down
			Arena::createExplosion(x, y, 2, isLast);
		if (dx == 0 && dy < 0) // left
			Arena::createExplosion(x, y, 3, isLast);
	}

	if (!isLast && !foundWall)
	{
		explodeBomb(x + dx, y + dy, dx, dy, step + 1, maxRadius);
	}
}

void Arena::createExplosion(int x, int y, int type, bool last)
{
	ArenaObjects::getInstance().explosions.push_back(
		Explosion(x, y, type, last)
	);
}

void Arena::addEnemy()
{
	//find a free position
	bool grid[Globals::BLOCKS_X][Globals::BLOCKS_Y] = { false };
	

	ArenaObjects objects = ArenaObjects::getInstance();
	for (int i = 0; i < objects.walls.size(); i++)
	{
		int x = objects.walls[i].getObjectX();
		int y = objects.walls[i].getObjectY();
		grid[x / BLOCK_H][y / BLOCK_W] = true;
	}
	for (int i = 0; i < objects.stones.size(); i++)
	{
		int x = objects.stones[i].getObjectX();
		int y = objects.stones[i].getObjectY();
		grid[x / BLOCK_H][y / BLOCK_W] = true;
	}

	Vector <Pair<int, int>> freePositions;
	for (int i = 0; i < Globals::BLOCKS_X; i++)
	{
		for (int j = 0; j < Globals::BLOCKS_Y; j++)
		{
			if (grid[i][j] == false)
			{
				freePositions.push_back(Pair<int, int>(i, j));
			}
		}
	}
	printf("%d\n", freePositions.size());
	int randomPosition = rand() % freePositions.size();
	Enemy enemy;
	int x = freePositions[randomPosition].first * BLOCK_H;
	int y = freePositions[randomPosition].second * BLOCK_W;
	printf("%d %d\n", x, y);
	enemy.setupAnimations();
	enemy.setPosition(x, y);
	enemy.setSpeed(4);
	objects.enemies.push_back(enemy);
}

void Arena::update()
{
	ArenaObjects objects = ArenaObjects::getInstance();

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
	for (int i = 0; i < objects.enemies.size(); i++)
	{
		//objects.enemies[i].makeMove();
	}
}

void Arena::drawArena()
{
	ArenaObjects objects = ArenaObjects::getInstance();
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
	for (int i = 0; i < objects.enemies.size(); i++)
	{
		objects.enemies[i].draw(
			objects.enemies[i].getObjectX(),
			objects.enemies[i].getObjectY(),
			objects.enemies[i].getObjectW(),
			objects.enemies[i].getObjectH()
		);
	}
}