#pragma once
#ifndef GAME_H
#define GAME_H

#include "Arena.h"
#include "Player.h"
#include "Pair.h"
#include "Queue.h"
#include "graphics.h"
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

	/**
		Main action loop, listens for events, updates the map and redraws it
	*/
	void gameLoop();



private:

	int height;
	int width;

	void capFPS(Uint32);

	Player player;

};

#endif /* GAME_H */

