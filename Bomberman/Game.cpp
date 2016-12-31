#include "Game.h"
#include "Pair.h"
#include <random>
#include <time.h>
#include "SDL_Image.h"
#include "KeyboardInput.h"

#define FPS 30
#define blockW Globals::BLOCK_WIDTH
#define blockH Globals::BLOCK_HEIGHT

Game::Game()
{
	Graphics::init();
	Arena::init();
	Arena::generateRandomArena();

	player.setPosition(30, 30);
	player.setSpeed(Globals::PLAYER_SPEED);
	player.setBox({ 30, 30, 17, 22 });

	this->loadTextures();
	this->setAnimations();
	this->gameLoop();
}

Game::~Game() {}


void Game::endGame()
{
	Graphics::destroy();
}

void Game::loadTextures()
{
	player.setSprite("Resources/second.png", { 125, 2, 15, 22 });
}

void Game::setAnimations()
{
	player.getSprite().addAnimationFrame("default", 125, 2, 15, 22);
	player.getSprite().setAnimation("default", 0);

	player.getSprite().addAnimationFrame("idle_up", 15, 2, 15, 22);
	player.getSprite().addAnimationFrame("idle_right", 69, 2, 15, 22);
	player.getSprite().addAnimationFrame("idle_down", 125, 2, 15, 22);
	player.getSprite().addAnimationFrame("idle_left", 179, 2, 17, 22);

	player.getSprite().addAnimationFrame("walk_up", 32, 2, 15, 22);
	player.getSprite().addAnimationFrame("walk_up", 49, 2, 15, 22);
		
	player.getSprite().addAnimationFrame("walk_right", 88, 2, 15, 22);
	player.getSprite().addAnimationFrame("walk_right", 107, 2, 15, 22);

	player.getSprite().addAnimationFrame("walk_down", 142, 2, 15, 22);
	player.getSprite().addAnimationFrame("walk_down", 159, 2, 15, 22);

	player.getSprite().addAnimationFrame("walk_left", 179, 2, 17, 22);
	player.getSprite().addAnimationFrame("walk_left", 198, 2, 17, 22);

}


void Game::printLevel()
{
	Graphics::clearRenderer();
	
	Arena::drawArena();
	player.draw();

	Graphics::drawRenderer();
}

void Game::gameLoop()
{
	KeyboardInput input;
	Uint32 starting_tick;
	int frameNumber = 0;

	while (true)
	{
		frameNumber++;
		starting_tick = SDL_GetTicks();
		input.newFrame();
		input.processInputs();
		
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			break;
		}
		if (input.isKeyHeld(SDL_SCANCODE_D))
		{
			player.moveRight();
		}
		if (input.isKeyHeld(SDL_SCANCODE_A))
		{
			player.moveLeft();
		}
		if (input.isKeyHeld(SDL_SCANCODE_W))
		{
			player.moveUp();
		}
		if (input.isKeyHeld(SDL_SCANCODE_S))
		{
			player.moveDown();
		}
		if (input.wasKeyPressed(SDL_SCANCODE_SPACE))
		{
			printf("Bomb placed\n");
			Bomb newBomb(
				player.getPosX(),
				player.getPosY(),
				Globals::DEFAUT_BOMB_DURATION
			);
			Arena::bombs.push_back(newBomb);
		}
		if (!player.moved())
		{
			player.idle();
		}
		for (int i = 0; i < Arena::bombs.size(); i++)
		{
			if (Arena::bombs[i].exploded())
			{
				Arena::bombs[i].explode();
				Arena::bombs.remove(i);
			}
			else
			{
				Arena::bombs[i].update();
			}
			
		}
		this->printLevel();
		
		this->capFPS(starting_tick);
		if (frameNumber == FPS) frameNumber = 0;
	}
	endGame();
}

void Game::capFPS(Uint32 startingTicks)
{
	if ( (1000 / FPS) > SDL_GetTicks() - startingTicks )
	{
		SDL_Delay( 1000 / FPS - (SDL_GetTicks() - startingTicks) );
	}
}

