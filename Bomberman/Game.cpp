#include "Game.h"
#include <algorithm>


#define blockW Globals::BLOCK_WIDTH
#define blockH Globals::BLOCK_HEIGHT

Game::Game()
{
	srand(time(0));
	Graphics::init();
	arena.init();
	arena.generateRandomArena();
	arena.addEnemy();
	arena.addEnemy();
	this->setupPlayer();
	this->gameLoop();
}

Game::~Game() {}


void Game::endGame()
{
	Graphics::destroy();
}

void Game::printLevel()
{
	Graphics::clearRenderer();
	
	arena.drawArena();
	player.draw();

	Graphics::drawRenderer();
}

void Game::gameLoop()
{
	KeyboardInput input;

	while (true)
	{
		const int FRAME_START = SDL_GetTicks();
		input.newFrame();
		input.processInputs();
		
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			break;
		}
		if (input.isKeyHeld(SDL_SCANCODE_D))
		{
			player.moveRight(arena.getObjects());
		}
		if (input.isKeyHeld(SDL_SCANCODE_A))
		{
			player.moveLeft(arena.getObjects());
		}
		if (input.isKeyHeld(SDL_SCANCODE_W))
		{
			player.moveUp(arena.getObjects());
		}
		if (input.isKeyHeld(SDL_SCANCODE_S))
		{
			player.moveDown(arena.getObjects());
		}
		if (input.wasKeyPressed(SDL_SCANCODE_SPACE))
		{
			arena.placeBomb(
				player.getObjectX(),
				player.getObjectY(),
				Globals::DEFAUT_BOMB_DURATION
			);
		}
		if (!player.moved())
		{
			player.idle();
		}


		this->update();
		this->printLevel();
		
		cap_FPS(FRAME_START);
		
	}
	endGame();
}

void Game::update()
{
	this->player.update(arena.getObjects(), arena.getEnemies());
	arena.update();
}

void Game::setupPlayer()
{
	player.init();
	player.setSpeed(PLAYER_SPEED);
	player.setBox({ 30, 30, 17, 22 });
	player.setDeathAnimationTime(500);

	player.setSprite("Resources/second.png", { 125, 2, 15, 22 }, 170);
	player.getSprite().addAnimationFrame("default", 125, 2, 15, 22);
	player.getSprite().setAnimation("default");

	player.getSprite().addAnimationFrame("idle_up", 15, 2, 15, 22);
	player.getSprite().addAnimationFrame("idle_right", 69, 2, 15, 22);
	player.getSprite().addAnimationFrame("idle_down", 125, 2, 15, 22);
	player.getSprite().addAnimationFrame("idle_left", 179, 2, 17, 22);

	player.getSprite().addAnimationFrame("walk_up", 32, 2, 15, 22);
	player.getSprite().addAnimationFrame("walk_up", 49, 2, 15, 22);

	player.getSprite().addAnimationFrame("walk_right", 87, 2, 15, 22);
	player.getSprite().addAnimationFrame("walk_right", 105, 2, 15, 22);

	player.getSprite().addAnimationFrame("walk_down", 142, 2, 15, 22);
	player.getSprite().addAnimationFrame("walk_down", 159, 2, 15, 22);

	player.getSprite().addAnimationFrame("walk_left", 179, 2, 17, 22);
	player.getSprite().addAnimationFrame("walk_left", 198, 2, 17, 22);

	player.getSprite().addAnimationFrame("die_1", 152, 176, 17, 23);
	player.getSprite().addAnimationFrame("die_2", 171, 175, 19, 24);
	player.getSprite().addAnimationFrame("die_3", 192, 174, 23, 25);
	player.getSprite().addAnimationFrame("die_4", 217, 174, 28, 25);
	player.setDeathFrames(4);
}

void Game::cap_FPS(const int FRAME_START)
{
	const int FRAME_END = SDL_GetTicks();
	const int ELAPSED = FRAME_END - FRAME_START;
	if (ELAPSED < MAX_FRAME_TIME)
		SDL_Delay(MAX_FRAME_TIME - ELAPSED);
}