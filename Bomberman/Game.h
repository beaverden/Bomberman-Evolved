#pragma once
#include "Arena.h"
#include "Player.h"
#include "Pair.h"
#include "Queue.h"
#include "graphics.h"
#include "Texture.h"
#include "AnimatedSprite.h"
#include "Vector.h"
#include "Object.h"

class Game
{
public:
	Game();
	~Game();

	/**
		Destroys all the objects and destoys graphics
	*/
	void endGame();


	void loadTextures();
	void setAnimations();


	/**
		Prints the game maze
		Prints only the changes between the new maze and old maze
	*/
	void printLevel();

	/*
		Main action loop, listens for events, updates the map and redraws it
	*/
	void gameLoop();
	
	bool movePlayer(int, int);



private:

	int height;
	int width;

	void capFPS(Uint32);

	Player player;

};

