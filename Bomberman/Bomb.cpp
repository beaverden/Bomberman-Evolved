#include "Bomb.h"


Bomb::Bomb() {}

Bomb::Bomb(int x, int y, int duration, int explosionRadius)
{
	Pair<int, int> blockPosition = getPlacementPosition(x, y);

	blockPosition.first  += (Globals::BLOCK_HEIGHT - BOMB_HEIGHT) / 2;
	blockPosition.second += (Globals::BLOCK_WIDTH  - BOMB_WIDTH) / 2;

	this->bombPosX = blockPosition.first;
	this->bombPosY = blockPosition.second;
	this->bombTime = duration;
	this->explosionRadius = explosionRadius;
	this->placedAt = std::clock();
	setAnimations();
}

Bomb::~Bomb() {}

Timestamp Bomb::getPlacedTime()
{
	return placedAt;
}

int Bomb::getBombTime()
{
	return bombTime;
}

void Bomb::setBombTime(int duration)
{
	this->bombTime = duration;
}

void Bomb::setExplosionArea(int area)
{
	this->explosionRadius = area;
}

void Bomb::update()
{
	double percentage = (getElapsed() / (double)bombTime);

	if (percentage < 0.10)
	{
		sprite.setAnimation("phase_1");
	}
	else if (percentage < 0.20)
	{
		sprite.setAnimation("phase_2");
	}
	else if (percentage < 0.30)
	{
		sprite.setAnimation("phase_3");
	}
	else if (percentage < 0.40)
	{
		sprite.setAnimation("phase_2");
	}
	else if (percentage < 0.50)
	{
		sprite.setAnimation("phase_1");
	}
	else if (percentage < 0.60)
	{
		sprite.setAnimation("phase_3");
	}
	else if (percentage < 0.70)
	{
		sprite.setAnimation("phase_1");
	}
	else if (percentage < 0.80)
	{
		sprite.setAnimation("phase_3");
	}
	else if (percentage < 0.90)
	{
		sprite.setAnimation("phase_2");
	}
}

bool Bomb::exploded()
{
	if (getElapsed() > bombTime) return true;
	return false;
}

void Bomb::explode()
{
	int blockX = bombPosX - bombPosX % Globals::BLOCK_HEIGHT;
	int blockY = bombPosY - bombPosY % Globals::BLOCK_WIDTH;
	explode(blockX, blockY, -Globals::BLOCK_HEIGHT, 0, 0);
	explode(blockX, blockY, 0, -Globals::BLOCK_WIDTH, 0);
	explode(blockX, blockY, 0, Globals::BLOCK_WIDTH, 0);
	explode(blockX, blockY, Globals::BLOCK_HEIGHT, 0, 0);
}


void Bomb::explode(int x, int y, int dx, int dy, int step)
{
	SDL_Rect rect = {
		x,
		y,
		Globals::BLOCK_WIDTH,
		Globals::BLOCK_HEIGHT
	};
	for (int i = 0; i < Arena::stones.size(); i++)
	{
		if (Arena::stones[i].equals(rect)) return;
	}
	for (int i = 0; i < Arena::walls.size(); i++)
	{
		if (Arena::walls[i].equals(rect))
		{
			Arena::walls.remove(i);
			return;
		}
	}
	if (step + 1 < this->explosionRadius)
	{
		explode(x + dx, y + dy, dx, dy, step + 1);
	}
}

int Bomb::getPosX()
{
	return this->bombPosX;
}

int Bomb::getPosY()
{
	return this->bombPosY;
}

AnimatedSprite& Bomb::getSprite()
{
	return this->sprite;
}

void Bomb::setAnimations()
{
	sprite.setTexture("Resources/sprites.png", { 181, 92, 17, 17 });
	sprite.addAnimationFrame("phase_1", 181, 92, 17, 17);
	sprite.addAnimationFrame("phase_2", 211, 92, 17, 17);
	sprite.addAnimationFrame("phase_3", 241, 92, 17, 17);
}

Timestamp Bomb::getElapsed()
{
	return (std::clock() - placedAt);
}

// Gets the point coordinates from the current player position
// Calculates the block square that this point is located in
Pair<int, int> Bomb::getPlacementPosition(int x, int y)
{
	int pointX = x + (4 * Globals::PLAYER_HEIGHT) / 10;
	int pointY = y + (5 * Globals::PLAYER_WIDTH) / 10;
	pointX -= pointX % Globals::BLOCK_HEIGHT;
	pointY -= pointY % Globals::BLOCK_WIDTH;
	return Pair<int, int>(pointX, pointY);
}