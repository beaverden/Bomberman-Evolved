#include "Game.h"
#include "Pair.h"
#include <random>
#include <time.h>
#include "SDL_Image.h"

#define FPS 60

Game::Game()
{
	srand(time(0));
	this->graphics.init(600, 600);
	this->initLevel(20, 20);
	this->loadTextures();
}


Game::~Game()
{
	playerPath.clear();
	updateCells.clear();
	freeTextures();
}

void Game::loadTextures()
{
	if (!grass.loadImage("Resources/grass.png"))
	{
		printf("Couldn't load grass: %s\n", SDL_GetError());
	}
	if (!stone.loadImage("Resources/stone.png"))
	{
		printf("Couldn't load stone: %s\n", SDL_GetError());
	}
	if (!wall.loadImage("Resources/wall.png"))
	{
		printf("Couldn't load wall: %s\n", SDL_GetError());
	}
}

void Game::freeTextures()
{
	SDL_FreeSurface(grass.getTexture());
	SDL_FreeSurface(stone.getTexture());
	SDL_FreeSurface(wall.getTexture());
}

void Game::initLevel(int height, int width)
{
	this->height = height;
	this->width = width;
	Maze initMaze(height, width);
	initMaze.generateMazeRandom(this->maze);
}

void Game::printBoard()
{
	
	graphics.reset(255, 255, 255);
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{		
			if (maze[i][j] == 0) 
			{
				grass.drawTo(graphics.getSurface(), j * 30, i * 30);
			}
			else if (maze[i][j] == -1)
			{
				stone.drawTo(graphics.getSurface(), j * 30, i * 30);
			}
			else if (maze[i][j] == -2)
			{
				wall.drawTo(graphics.getSurface(), j * 30, i * 30);
			}
		}
	}
	graphics.update();
}

Uint32 Game::getColorAt(int y, int x)
{
	switch (this->maze[y][x])
	{
	case -1: return graphics.getColor(0, 0, 0); break;
	case -2: return graphics.getColor(0, 50, 50); break;
	case 2: return graphics.getColor(0, 0, 0); break;
	case 1: return graphics.getColor(255, 0, 0); break;
	case 0: return graphics.getColor(255, 255, 255); break;
	default: return graphics.getColor(255, 255, 255);
	}
}

void Game::gameLoop()
{
	SDL_Event event;
	Uint32 starting_tick;
	bool running = true;

	while (running)
	{
		starting_tick = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			//printf("%d\n", event.type);
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_UP)
				{
					this->movePlayer(-1, 0);
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					this->movePlayer(1, 0);
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					this->movePlayer(0, 1);
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					this->movePlayer(0, -1);
				}
			}
			
		}
		this->printBoard();
		
		this->capFPS(starting_tick);
	}
}

void Game::capFPS(Uint32 startingTicks)
{
	if ( (1000 / FPS) > SDL_GetTicks() - startingTicks )
	{
		SDL_Delay( 1000 / FPS - (SDL_GetTicks() - startingTicks) );
	}
}

bool Game::canMove(Player p, int dy, int dx)
{
	int x = p.getPosX() + dx,
		y = p.getPosY() + dy;

	if (x < 0 || y < 0 || x >= this->width || y >= this->width) return false;
	if (this->maze[y][x] == -1 || this->maze[y][x] == -2) return false;
	return true;
}

void Game::movePlayer(int dy, int dx)
{

	if (canMove(this->player, dy, dx))
	{
		int oldX = this->player.getPosX(),
			oldY = this->player.getPosY();
		this->setCell(oldY, oldX, 0);

		this->player.moveBy(dy, dx);
		int newX = this->player.getPosX(),
			newY = this->player.getPosY();

		this->setCell(newY, newX, 1);

		this->updateCells.push(Pair<int, int>(newY, newX));
		this->updateCells.push(Pair<int, int>(oldY, oldX));
	}
}

void Game::setPlayerPath()
{
	int playerX = this->player.getPosX(),
		playerY = this->player.getPosY();

	Maze maze(this->height, this->width);

	this->resetPath();

	this->playerPath = maze.calculatePath(this->maze, { playerY, playerX }, { this->height - 2, this->width - 2 });


	this->playerPath.iterator();
	while (!this->playerPath.isNull())
	{
		int y = this->playerPath.curr().y,
			x = this->playerPath.curr().x;

		if (this->setCell(y, x, 2))
		{
			this->updateCells.push(Pair<int, int>(y, x));
		}
		
		this->playerPath.next();
	}
}

void Game::resetPath()
{
	this->playerPath.iterator();
	while (!this->playerPath.isNull())
	{
		int y = this->playerPath.curr().y,
			x = this->playerPath.curr().x;

		if (this->maze[y][x] != 1) 
		//Don't reset player cell
		{
			if (this->setCell(y, x, 0))
			{
				this->updateCells.push(Pair<int, int>(y, x));
			}
		}
		
		
		this->playerPath.next();
	}
}

bool Game::setCell(int y, int x, char newData)
{
	char curr = this->maze[y][x];
	bool allow = false;

	if (curr == newData)
	{
		return false;
	}

	if (curr == 0)
	{
		allow = true;	
	}
	else if (curr == 1)
	{
		if (newData == 0)
		{
			allow = true;
		}
	}
	else if (curr == 2)
	{
		allow = true;
	}
	if (allow)
	{
		this->maze[y][x] = newData;
		return true;
	}
	return false;
}