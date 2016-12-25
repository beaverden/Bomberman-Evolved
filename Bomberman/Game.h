#pragma once
#include "Maze.h"
#include "Player.h"
#include "Pair.h"
#include "Queue.h"
#include "graphics.h"
#include "Texture.h"

class Game
{
public:
	Game();
	~Game();

	void loadTextures();
	void freeTextures();

	/*
		@param height of the maze
		@param width of the maze
		Initializes and generates the maze
		Sets the player position to 1,1
	*/
	void initLevel(int, int);


	/* 
		Prints the game maze
		Prints only the changes between the new maze and old maze
	*/
	void printBoard();

	/*
		@param y position on the maze
		@param x position on the maze
		Returns the zone color specified by the game maze
	*/
	Uint32 getColorAt(int, int);


	void gameLoop();

	void movePlayer(int, int);
	void setPlayerPath();

	bool setCell(int, int, char);

private:	
	int height;
	int width;

	char maze[Maze::MAX_MAZE_HEIGHT][Maze::MAX_MAZE_WIDTH];
	LinkedList <Player> players;

	Graphics graphics;
	void capFPS(Uint32);

	Player player;
	Stack <Maze::cell> playerPath;
	void resetPath();

	bool canMove(Player, int, int);

	Queue <Pair<int, int>> updateCells;

	Texture grass;
	Texture stone;
	Texture wall;
};

