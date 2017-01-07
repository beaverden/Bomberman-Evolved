#include "Arena.h"
#include "ArenaObjects.h"



void Arena::placeBomb(int x, int y, int duration)
{
	objects.bombs.push_back(Bomb(x, y, duration));
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