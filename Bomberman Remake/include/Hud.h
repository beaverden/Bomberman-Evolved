#pragma once
#ifndef HUD_H
#define HUD_H

#include "Arena.h"
#include "Player.h"
#include "graphics.h"
#include "globals.h"
#include <ctime>

#define HUD_HEIGHT Globals::SCREEN_HEIGHT - Globals::ARENA_HEIGHT
#define HUD_WIDTH Globals::SCREEN_WIDTH
#define HUD_X Globals::ARENA_HEIGHT
#define HUD_Y 0
#define GAME_MAX_TIME_S 120

class Hud
{
public:
	Hud();
	~Hud();

	void init();

	void setArena(Arena* arena);

	void setPlayer(Player* player);

	void draw();

	void resetTimer();

	int getStartTime();

private:
	Arena* arena;
	Player* player;

	SDL_Surface* hud;
	Sprite playerDefault;
	Sprite enemyDefault;
	Sprite heart;

	int startTime;

	void drawPlayerLives();
	void drawEnemyCount();
	void drawTimer();
};

#endif /* HUD_H */

