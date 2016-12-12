#pragma once
#include "Maze.h"
#include "Player.h"
#include "Pair.h"
#include "Queue.h"
#include "graphics.h"
class Game
{
public:
	Game();
	~Game();

	/*
		@param height of the maze
		@param width of the maze
		Initializes and generates the maze
		Sets the player position to 1,1
	*/
	void initLevel(int, int);

	/* 
		Prints the game board
		Prints only the changes between the new board and old board
	*/
	void printBoard();

	/*
		@param y position on the board
		@param x position on the board
		Returns the zone color specified by the game board
	*/
	Uint32 getColorAt(int, int);


	void gameLoop();

	void movePlayer(int, int);
	void setPlayerPath();

	bool setCell(int, int, char);

private:	
	int height;
	int width;
	bool printedForFirstTime;
	char board[Maze::MAX_MAZE_HEIGHT][Maze::MAX_MAZE_WIDTH];
	char previousBoard[Maze::MAX_MAZE_HEIGHT][Maze::MAX_MAZE_WIDTH];

	Graphics graphics;
	void capFPS(Uint32);

	Player player;
	Stack <Maze::cell> playerPath;
	void resetPath();

	bool canMove(Player, int, int);

	Queue <Pair<int, int>> updateCells;


};

