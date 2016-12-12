
#pragma once
#include "LinkedList.h"
#include "Stack.h"

class Maze
{
public:

	Maze(int, int);
	~Maze();

	static const int MAX_MAZE_HEIGHT = 101;
	static const int MAX_MAZE_WIDTH = 101;
	int mazeHeight;
	int mazeWidth;

	struct cell
	{
		int y;
		int x;

		/*
		@param char y, char x - supposed position
		@return true if the cell is in the boundaries of the arena
		*/
		bool exists(int y, int x, const int ARENA_HEIGHT, const int ARENA_WIDTH);

		bool exists(const int ARENA_HEIGHT, const int ARENA_WIDTH);

		bool isWall(int y, int x);

		bool operator!=(const cell &that);

		/*
		Finds the common wall between two cells
		@param first cell and the second cell
		@return common wall between them or an undefined value if there is no common wall
		*/
		static cell commonWall(cell a, cell b);

		/*
		Finds all the cell's neighbours and lists them
		@return a linked list containing all the cell's neighbours
		*/
		LinkedList <cell> getNeighbours(const int, const int);
	};

	//Accepts only odd sizes
	void generateMazeDFS(char[Maze::MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH]);

	void generateMazeRandom(char [Maze::MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH]);

	Stack<Maze::cell> calculatePath(char[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH], cell, cell);

	/*
	Removes percent% random walls from the maze
	@param maze to be randomized
	@param the percent of walls to be turned into path
	*/
	void randomizedGaps(char[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH], int);

	/*
	@param the maze to be randomized
	@param maxNumber of corridors to be created
	@param maxDepth of the corridor
	*/
	void randomizedCorridors(char[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH], int, int);

	bool cellCanBeChanged(int, int);

private:
	Stack <cell> reconstructPath(cell, cell, short[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH]);

	void resetArray(char maze[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH]);
};
