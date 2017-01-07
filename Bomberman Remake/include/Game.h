#pragma once
#ifndef GAME_H
#define GAME_H

#include "Object.h"
#include "AnimatedSprite.h"
#include "KeyboardInput.h"
#include "Arena.h"
#include "Player.h"

#include "SoundEffects.h"
#include "graphics.h"
#include "Hud.h"



#define FPS 50
#define MAX_FRAME_TIME 1000 / FPS
#define PLAYER_SPEED 2.2f

class SceneController;

class Game
{
public:
	Game();
	~Game();

	/*
	Destroys all the objects and destoys graphics
	*/
	void endGame();

	void resetGame();

	/**
		Main action loop, listens for events, updates the map and redraws it
	*/
	void gameLoop();

	void cap_FPS(const int FRAME_START);

	bool timeOver();

	Player player;
	void setupPlayer();

	
	Arena arena;
	Hud hud;
	SceneController* scenes;
	bool ended;
};

#endif /* GAME_H */

