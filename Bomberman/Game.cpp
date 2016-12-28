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
	int start;
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
	SDL_Event event;
	Uint32 starting_tick;
	int frameNumber = 0;
	bool running = true;

	while (running)
	{
		frameNumber++;
		input.newFrame();
		starting_tick = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.repeat == 0)
				{
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT)
			{
				return;
			}
		}

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			running = false;
			break;
		}
		if (input.isKeyHeld(SDL_SCANCODE_D))
		{
			this->movePlayer(0, 4);
			player.getSprite().playAnimation("walk_right");
			
		}
		if (input.isKeyHeld(SDL_SCANCODE_A))
		{
			this->movePlayer(0, -4);
			player.getSprite().playAnimation("walk_left");
		}
		if (input.isKeyHeld(SDL_SCANCODE_W))
		{
			this->movePlayer(-4, 0);
			player.getSprite().playAnimation("walk_up");
		}
		if (input.isKeyHeld(SDL_SCANCODE_S))
		{
			this->movePlayer(4, 0);
			player.getSprite().playAnimation("walk_down");
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


bool Game::movePlayer(int dx, int dy)
{
	if (player.canMove(dx, dy, Arena::stones, Arena::walls))
	{
		this->player.moveBy(dx, dy);
	}
	else
	{
		return false;
	}
	
	return true;
}
