#include "Game.h"
#include "ConsoleOutput.h"
#include "Pair.h"

Game::Game()
{
	this->printedForFirstTime = false;
}


Game::~Game()
{
}

void Game::initLevel(int height, int width)
{
	this->height = height;
	this->width = width;
	Maze initMaze(height, width);
	initMaze.generateMaze(this->board);
	this->board[1][1] = 1; //Player
}

void Game::printBoard()
{
	this->setPlayerPath();

	if (!this->printedForFirstTime)
	{
		ConsoleOutput::cls();
		ConsoleOutput::setCursorAt(0, 0);
		this->printedForFirstTime = true;
		for (int i = 0; i < this->height; i++)
		{
			for (int j = 0; j < this->width; j++)
			{
				char charToPrint = this->getCharAt(i, j);
				char color = this->getColorAt(i, j);
				ConsoleOutput::setChar(j, i, charToPrint, color);
			}
		}
	}
	else
	{
		while (!updateCells.empty())
		{
			int y = this->updateCells.front().first();
			int x = this->updateCells.front().second();
			ConsoleOutput::setChar(x, y, this->getCharAt(y, x), this->getColorAt(y, x));
			this->updateCells.pop();
		}
	}
}

char Game::getCharAt(int y, int x)
{
	switch (this->board[y][x])
	{
	case -1: return '@'; break;
	case 0: return ' '; break;
	case 1: return (char)1; break;
	case 2: return '.'; break;
	default: return '@'; break;
	}
}

unsigned short Game::getColorAt(int y, int x)
{
	switch (this->board[y][x])
	{
	case 1: return ConsoleOutput::getColor(ConsoleOutput::RED, 1, 0); break;
	case -1: return ConsoleOutput::getColor(ConsoleOutput::YELLOW, 0, 0);
	case 2: return ConsoleOutput::getColor(ConsoleOutput::RED, 0, 0);
	default: return ConsoleOutput::WHITE; 
	}
}

bool Game::canMove(Player p, int dy, int dx)
{
	int x = p.getPosX() + dx,
		y = p.getPosY() + dy;

	if (x < 0 || y < 0 || x >= this->width || y >= this->width) return false;
	if (this->board[y][x] == -1) return false;
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
	Stack <Maze::cell> path = maze.calculatePath(this->board, { playerY, playerX }, { this->height - 2, this->width - 2 });

	path.iterator();
	while (!path.isNull())
	{
		int y = path.curr().y,
			x = path.curr().x;
		if (board[y][x] != 2)
		{
			this->updateCells.push(Pair<int, int>(y, x));
		}
		this->setCell(y, x, 2);
		
		path.next();
	}
}

void Game::setCell(int y, int x, char newData)
{
	char curr = this->board[y][x];
	bool allow = false;

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
		this->board[y][x] = newData;
	}
}