#pragma once

class Player
{
public:
	Player() 
	{
		this->posX = 1;
		this->posY = 1;
		this->oldPosX = 1;
		this->oldPosY = 1;
	}
	~Player();

	void move(int y, int x)
	{
		this->oldPosX = this->posX;
		this->oldPosY = this->posY;
		this->posX = x;
		this->posY = y;

	}

	void moveBy(int dy, int dx)
	{
		this->oldPosX = this->posX;
		this->oldPosY = this->posY;
		this->posX += dx;
		this->posY += dy;
	}

	int getPosX()
	{
		return this->posX;
	}

	int getPosY()
	{
		return this->posY;
	}

	int getOldPosX()
	{
		return this->oldPosX;
	}

	int getOldPosY()
	{
		return this->oldPosY;
	}

private:
	int posX;
	int posY;
	int oldPosX;
	int oldPosY;
};

