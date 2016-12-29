#include "Bomb.h"


Bomb::Bomb() {}

Bomb::Bomb(int x, int y, int duration, int explosionArea)
{
	Pair<int, int> blockPosition = getPlacementPosition(x, y);

	blockPosition.first += (Globals::BLOCK_HEIGHT - BOMB_HEIGHT) / 2;
	blockPosition.second += (Globals::BLOCK_WIDTH - BOMB_WIDTH) / 2;

	this->bombPosX = blockPosition.first;
	this->bombPosY = blockPosition.second;
	this->bombTime = duration;
	this->explosionArea = explosionArea;
	this->placedAt = std::clock();
	setAnimations();
}

Bomb::~Bomb()
{
}

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
	this->explosionArea = area;
}

void Bomb::update()
{
	double percentage = (getElapsed() / (double)bombTime);
	if (percentage < 0.33)
	{
		sprite.setAnimation("phase1");
	}
	else if (percentage < 0.66)
	{
		sprite.setAnimation("phase2");
	}
	else
	{
		sprite.setAnimation("phase3");
	}
}

bool Bomb::exploded()
{
	auto now = std::clock();
	if (placedAt + bombTime >= now) return true;
	return false;
}

void Bomb::explode()
{
	explode(bombPosX, bombPosY, -1, 0, 0);
	explode(bombPosX, bombPosY, 1, 0, 0);
	explode(bombPosX, bombPosY, 0, -1, 0);
	explode(bombPosX, bombPosY, 0, 1, 0);
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
		if (Arena::stones[i].collides(rect)) return;
	}
	for (int i = 0; i < Arena::walls.size(); i++)
	{
		if (Arena::walls[i].collides(rect))
		{
			Arena::walls.remove(i);

		}
	}
	if (step < this->explosionArea)
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
	sprite.setTexture("Resources/sprites.png", { 181, 93, 16, 16 });
	sprite.addAnimationFrame("plase_1", 181, 93, 16, 16);
	sprite.addAnimationFrame("phase_2", 211, 91, 16, 16);
	sprite.addAnimationFrame("phase_3", 241, 91, 16, 16);
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