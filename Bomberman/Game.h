#pragma once
#include "Maze.h"
#include "Player.h"
#include "Pair.h"
#include "Queue.h"

class Game
{
public:
	Game();
	~Game();

	void initLevel(int, int);

	/* Prints the game board
	Prints only the changes between the new board and old board
	*/
	void printBoard();

	/* Returns the number at board[y][x] in the printable format
	*/
	char getCharAt(int, int);
	unsigned short getColorAt(int, int);

	void movePlayer(int, int);
	void setPlayerPath();

	void setCell(int, int, char);

private:	
	int height;
	int width;
	bool printedForFirstTime;
	char board[Maze::MAX_MAZE_HEIGHT][Maze::MAX_MAZE_WIDTH];
	char previousBoard[Maze::MAX_MAZE_HEIGHT][Maze::MAX_MAZE_WIDTH];

	Player player;

	bool canMove(Player, int, int);

	Queue <Pair<int, int>> updateCells;

};

