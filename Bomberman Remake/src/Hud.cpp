#include "Hud.h"
#include <string>


Hud::Hud() {}

Hud::~Hud() {}

void Hud::init()
{
	const Vector<Enemy>& enemies = arena->getEnemies();
	SDL_Rect defaultRectEnemy = enemies[0].getSprite().getAnimationFrame("default");

	this->enemyDefault.setTexture(
		enemies[0].getSprite().getTexture(),
		defaultRectEnemy
	);

	SDL_Rect defaultRectPlayer = player->getSprite().getAnimationFrame("default");
	this->playerDefault.setTexture(
		player->getSprite().getTexture(),
		defaultRectPlayer
	);

	heart.setTexture("Resources/Images/heart.png");
	heart.setRect({ 0, 0, 170, 150 });

	this->startTime = SDL_GetTicks();
}

void Hud::setArena(Arena* arena)
{
	this->arena = arena;


}

void Hud::setPlayer(Player* player)
{
	this->player = player;
}

void Hud::draw()
{
	SDL_Color gray = { 127, 127, 127 };
	SDL_Rect hudRect = { HUD_X, HUD_Y, HUD_WIDTH, HUD_HEIGHT };
	Graphics::setRendererDrawColor(gray);
	SDL_RenderFillRect(Graphics::getRenderer(), &hudRect);

	drawPlayerLives();
	drawEnemyCount();
	drawTimer();
}

void Hud::drawPlayerLives()
{
	//adding player to hud
	const int PLAYER_DEFAULT_H = 10 + playerDefault.getRect().h;
	const int PLAYER_DEFAULT_W = 4 + playerDefault.getRect().w;
	const int PLAYER_DEFAULT_X = HUD_X + (HUD_HEIGHT - PLAYER_DEFAULT_H) / 2;
	const int PLAYER_DEFAULT_Y = 50;

	playerDefault.draw(
		PLAYER_DEFAULT_X, 
		PLAYER_DEFAULT_Y,
		PLAYER_DEFAULT_W,
		PLAYER_DEFAULT_H
	);

	const int HEART_W = 20;
	const int HEART_H = 16;
	for (int i = 1; i <= player->getLives(); i++)
	{
		int HEART_X = PLAYER_DEFAULT_X + (PLAYER_DEFAULT_H - HEART_H) / 2;
		int HEART_Y = PLAYER_DEFAULT_Y + (HEART_W + 7) * i;
		heart.draw(
			HEART_X,
			HEART_Y,
			HEART_W,
			HEART_H
		);
	}
}

void Hud::drawEnemyCount()
{
	//adding enemy to hud
	const int ENEMY_DEFAULT_H = 10 + enemyDefault.getRect().h;
	const int ENEMY_DEFAULT_W = 4 + enemyDefault.getRect().w;
	const int ENEMY_DEFAULT_X = HUD_X + (HUD_HEIGHT - ENEMY_DEFAULT_H) / 2;
	const int ENEMY_DEFAULT_Y = HUD_WIDTH - 100 - ENEMY_DEFAULT_W;
	enemyDefault.draw(
		ENEMY_DEFAULT_X, 
		ENEMY_DEFAULT_Y,
		ENEMY_DEFAULT_W,
		ENEMY_DEFAULT_H
	);

	std::string enemies = "x " + std::to_string(arena->getEnemies().size());
	const int FONT_SIZE = 20;

	const int TEXT_W = 40;
	const int TEXT_H = 25;
	const int TEXT_X = ENEMY_DEFAULT_X - (TEXT_H - ENEMY_DEFAULT_H) / 2;
	const int TEXT_Y = ENEMY_DEFAULT_Y + ENEMY_DEFAULT_W + 10;

	SDL_Rect text = {
		TEXT_Y,
		TEXT_X,
		TEXT_W,
		TEXT_H
	};
	Graphics::addText(
		enemies,
		"OpenSans20",
		"Resources/Fonts/OpenSans-Regular.ttf",
		FONT_SIZE,
		{ 255, 255, 255 },
		&text
	);
}

void Hud::drawTimer()
{
	const int CURRENT_TIME_MS = SDL_GetTicks();
	const int DIFF_TIME_MS = CURRENT_TIME_MS - startTime;
	const int DIFF_TIME_S = DIFF_TIME_MS / 1000;

	const int TIME_LEFT_S = GAME_MAX_TIME_S - DIFF_TIME_S;

	const int TIME_LEFT_MIN = TIME_LEFT_S / 60;
	const int TIME_LEFT_SEC = TIME_LEFT_S % 60;
	std::string time = std::to_string(TIME_LEFT_MIN) + ":" + std::to_string(TIME_LEFT_SEC);
	const int FONT_SIZE = 35;

	const int TEXT_W = 120;
	const int TEXT_H = 30;
	const int TEXT_X = HUD_X + (HUD_HEIGHT - TEXT_H) / 2;
	const int TEXT_Y = (HUD_WIDTH - TEXT_W) / 2;

	SDL_Rect text = {
		TEXT_Y,
		TEXT_X,
		TEXT_W,
		TEXT_H
	};
	Graphics::addText(
		time,
		"OpenSans20",
		"Resources/Fonts/OpenSans-Regular.ttf",
		FONT_SIZE,
		{ 255, 255, 255 },
		&text
	);

}

void Hud::resetTimer()
{
	this->startTime = SDL_GetTicks();
}

int Hud::getStartTime()
{
	return this->startTime;
}