#include "Arena.h"
#include "ArenaObjects.h"
#include "Enemy.h"

void Arena::addEnemy()
{
	//all positions are free
	bool grid[Globals::BLOCKS_X][Globals::BLOCKS_Y] = { false };

	//ocupy the positions with already existing objects
	//All the objects have positions that are multiples of 
	//BLOCK_H and BLOCK_W

	for (int i = 0; i < objects.walls.size(); i++)
	{
		int x = (int)objects.walls[i].getObjectX();
		int y = (int)objects.walls[i].getObjectY();
		grid[x / BLOCK_H][y / BLOCK_W] = true;
	}
	for (int i = 0; i < objects.stones.size(); i++)
	{
		int x = (int)objects.stones[i].getObjectX();
		int y = (int)objects.stones[i].getObjectY();
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

	int randomPosition = rand() % freePositions.size();
	Enemy enemy;
	int x = freePositions[randomPosition].first * BLOCK_H;
	int y = freePositions[randomPosition].second * BLOCK_W;

	setupEnemy(x, y);
}


void Arena::setupEnemy(int x, int y)
{
	Enemy enemy;
	enemy.init();
	enemy.setSpeed(this->enemySpeed);
	enemy.setBox({
		(float)x,
		(float)y,
		(float)BLOCK_W,
		(float)BLOCK_H
	});
	enemy.setDeathAnimationTime(ENEMY_DEATH_TIME_MS);
	enemy.getSprite().setTimeToUpdate(ENEMY_ANIMATION_UPDATE_MS);
	enemy.setupAnimations();
	enemy.setDeathFrames(0);

	enemies.push_back(enemy);
}

void Arena::addEnemies(int enemies)
{
	for (int i = 0; i < enemies; i++)
	{
		this->addEnemy();
	}
}