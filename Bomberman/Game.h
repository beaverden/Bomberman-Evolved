#pragma once
#ifndef GAME_H
#define GAME_H

#include "Object.h"
#include "AnimatedSprite.h"
#include "KeyboardInput.h"
#include "Arena.h"
#include "Player.h"

#include "graphics.h"


#define FPS 50
#define MAX_FRAME_TIME 1000 / FPS
#define PLAYER_SPEED 2.2f

class Game
{
public:
	Game();
	~Game();

private:
	/**
		Destroys all the objects and destoys graphics
	*/
	void endGame();


	/**
		Prints the game maze
		Prints only the changes between the new maze and old maze
	*/
	void printLevel();

	/**
		Main action loop, listens for events, updates the map and redraws it
	*/
	void gameLoop();

	void update();

	void setupPlayer();


	Player player;

	Arena arena;

	void cap_FPS(const int FRAME_START);

};

#endif /* GAME_H */

