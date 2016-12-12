#include <time.h>
#include <random>
#include "Maze.h"
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"
#include <limits.h>
#include "Pair.h"

#define MAX_HEIGHT Maze::MAX_MAZE_HEIGHT
#define MAX_WIDTH Maze::MAX_MAZE_WIDTH

/*
Implements methods from class Maze and it's struct cell
*/

Maze::Maze(int height, int width)
{
	this->mazeHeight = height;
	this->mazeWidth = width;
}


Maze::~Maze()
{
}


void Maze::resetArray(char maze[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH])
{
	for (int i = 0; i < this->mazeHeight; i++)
	{
		for (int j = 0; j < this->mazeWidth; j++)
		{
			if (i % 2 == 1 && j % 2 == 1)
			{
				maze[i][j] = 0;
			}
			else
			{
				maze[i][j] = -1;
			}
		}
	}
}


void Maze::generateMazeDFS(char maze[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH])
{
	Stack <cell> mainStack;
	bool visited[MAX_HEIGHT][MAX_WIDTH] = { false };

	resetArray(maze);

	cell first = { 1, 1 };
	visited[first.y][first.x] = true;

	int unvisitedCells = (this->mazeHeight / 2) * (this->mazeWidth / 2) - 1;

	mainStack.push(first);

	while (!mainStack.empty())
	{

		cell current = mainStack.top();
		LinkedList <cell> neighbours = current.getNeighbours(this->mazeHeight, this->mazeWidth);
		//printf("CURRENT CELL : %d %d \n", current.y, current.x);
		//Iterate over and select only unvisited neighbours
		LinkedList <cell> unvisitedNeighbours;
		neighbours.iterator();
		while (!neighbours.isNull())
		{
			cell neighbour = neighbours.curr();
			if (!visited[neighbour.y][neighbour.x])
			{
				unvisitedNeighbours.push_back(neighbour);
			}
			neighbours.next();
		}

		int unvisitedNeighboursSize = unvisitedNeighbours.size();

		//No unvisited neighbours available: pop the stack
		if (unvisitedNeighboursSize == 0)
		{
			if (!mainStack.empty())
			{
				mainStack.pop();
			}
		}
		//Found a unvisited cell, remove the wall between current and that cell, push it into the stack
		else
		{
			int randomNeighbourIndex = rand() % unvisitedNeighboursSize;
			Maze::cell randomNeigbourCell = unvisitedNeighbours.get(randomNeighbourIndex);

			mainStack.push(randomNeigbourCell);

			Maze::cell commonWall = Maze::cell::commonWall(current, randomNeigbourCell);
			visited[randomNeigbourCell.y][randomNeigbourCell.x] = true;
			if (commonWall.exists(this->mazeHeight, this->mazeWidth))
			{
				maze[commonWall.y][commonWall.x] = 0;
			}
		}

	}
}

void Maze::generateMazeRandom(char maze[Maze::MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH])
{
	for (int i = 0; i < this->mazeHeight; i++)
	{
		for (int j = 0; j < this->mazeWidth; j++)
		{
			if (i == 0 || j == 0 || i == this->mazeHeight - 1 || j == this->mazeWidth - 1)
			{
				maze[i][j] = -1;
			}
			else if (
				i % 2 == 1 && j % 2 == 1 &&
				i > 2 && i < this->mazeHeight - 3 &&
				j > 2 && j < this->mazeWidth - 3)
			{
				maze[i][j] = -1;
			}
			else
			{
				maze[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < 200; i++)
	{
		int rx = 1 + rand() % (this->mazeWidth - 2),
			ry = 1 + rand() % (this->mazeHeight - 2);
		if (maze[ry][rx] == 0)
		{
			maze[ry][rx] = -2;
		}
		
	}

}


Stack<Maze::cell> Maze::calculatePath(char maze[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH], cell start, cell end)
{
	short minDistance[MAX_HEIGHT][MAX_WIDTH];
	for (int i = 0; i < this->mazeHeight; i++)
	{
		for (int j = 0; j < this->mazeWidth; j++)
		{
			minDistance[i][j] = -1;
		}
	}

	int dy[] = { -1, 1, 0, 0 },
		dx[] = { 0, 0, -1, 1 };

	Queue <Maze::cell> currentQueue;
	minDistance[start.y][start.x] = 0;
	currentQueue.push(start);
	while (!currentQueue.empty())
	{
		Maze::cell current = currentQueue.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			int newY = current.y + dy[dir],
				newX = current.x + dx[dir];
			//If the coordinate is out of bounds - proceed to the next coordinate
			if (newY <= 0 || newY >= this->mazeHeight || newX <= 0 || newX >= this->mazeWidth) continue;
			//If the coordinate is a wall - proceed to the next coordinate
			if (maze[newY][newX] == -1) continue;
			//If the is a way to this cell already - continue
			if (minDistance[newY][newX] != -1 || minDistance[newY][newX] == 0) continue;

			minDistance[newY][newX] = minDistance[current.y][current.x] + 1;
			if (newY == end.y && newX == end.x)
			{
				break;
			}
			currentQueue.push({ newY, newX });
		}
	}

	return reconstructPath(start, end, minDistance);
}


Stack <Maze::cell> Maze::reconstructPath(cell start, cell finish, short minDistance[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH])
{
	int dy[] = { -1, 1, 0, 0 },
		dx[] = { 0, 0, -1, 1 };

	Stack <Maze::cell> reconstructedPath;

	if (minDistance[finish.y][finish.x] == -1) return reconstructedPath;

	Maze::cell walkBack = finish;
	while (walkBack != start)
	{
		reconstructedPath.push(walkBack);
		for (int dir = 0; dir < 4; dir++)
		{
			int newY = walkBack.y + dy[dir],
				newX = walkBack.x + dx[dir];
			//If the coordinate is out of bounds - proceed to the next coordinate
			if (newY <= 0 || newY >= this->mazeHeight || newX <= 0 || newX >= this->mazeWidth) continue;
			if (minDistance[newY][newX] == minDistance[walkBack.y][walkBack.x] - 1)
			{
				walkBack = { newY, newX };
				break;
			}
		}
	}

	reconstructedPath.push(start);
	return reconstructedPath;
}


void Maze::randomizedGaps(char maze[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH], int percent)
{
	Pair<int, int> walls[MAX_MAZE_HEIGHT*MAX_MAZE_WIDTH];
	int wallsSize = 0;

	for (int i = 1; i < this->mazeHeight - 1; i++)
	{
		for (int j = 1; j < this->mazeWidth - 1; j++)
		{
			if (maze[i][j] == -1)
			{
				walls[wallsSize++] = Pair<int, int>(i, j);
			}
		}
	}
	//Take down only 7% of the walls if the count is not specified
	int amount = 0;
	if (percent == -1) amount = (int)((0.07)*wallsSize);
	else amount = (int)((percent / 100.0)*wallsSize);

	while (amount--)
	{
		int randomPosition = rand() % wallsSize;
		Pair<int, int> randomWall = walls[randomPosition];
		while (maze[randomWall.first()][randomWall.second()] != -1)
		{
			randomPosition = rand() % wallsSize;
			randomWall = walls[randomPosition];
		}

		maze[randomWall.first()][randomWall.second()] = 0;

	}
}


void Maze::randomizedCorridors(char maze[MAX_MAZE_HEIGHT][MAX_MAZE_WIDTH], int number, int maxDepth)
{

	while (number--)
	{
		int startingY = 1 + rand() % (this->mazeHeight - 1);
		int startingX = 1 + rand() % (this->mazeWidth - 1);
		int depthX = 2 + rand() % (maxDepth - 2);
		int depthY = 2 + rand() % (maxDepth - 2);
		
		int dx = 0,
			dy = 0;
		for (int i = 0; i < depthX; i++)
		{
			int dirOneX = startingX + dx,
				dirOneY = startingY + dy,
				dirTwoX = startingX - dx,
				dirTwoY = startingY - dy;
			if (cellCanBeChanged(dirOneY, dirOneX))
			{
				maze[dirOneY][dirOneX] = 0;
			}
			if (cellCanBeChanged(dirTwoY, dirTwoX))
			{
				maze[dirTwoY][dirTwoX] = 0;
			}
			dx += 1;
		}

		for (int i = 0; i < depthY; i++)
		{
			int dirOneX = startingX + dx,
				dirOneY = startingY + dy,
				dirTwoX = startingX - dx,
				dirTwoY = startingY - dy;
			if (cellCanBeChanged(dirOneY, dirOneX))
			{
				maze[dirOneY][dirOneX] = 0;
			}
			if (cellCanBeChanged(dirTwoY, dirTwoX))
			{
				maze[dirTwoY][dirTwoX] = 0;
			}
			dy += 1;
		}
	}
}

bool Maze::cellCanBeChanged(int y, int x)
{
	return (y > 0 && x > 0 && y < this->mazeHeight - 1 && x < this->mazeWidth - 1);
}

/* CELL STRUCT IMPLEMENTATION */
bool Maze::cell::exists(int y, int x, const int ARENA_HEIGHT, const int ARENA_WIDTH)
{
	return (y >= 0 && x >= 0 && y < ARENA_HEIGHT && x < ARENA_WIDTH);
}

bool Maze::cell::exists(const int ARENA_HEIGHT, const int ARENA_WIDTH)
{
	return exists(this->y, this->x, ARENA_HEIGHT, ARENA_WIDTH);
}

bool Maze::cell::isWall(int y, int x)
{
	return (y % 2 == 0 || x % 2 == 0);
}

bool Maze::cell::operator!=(const cell &that)
{
	return (this->x != that.x || this->y != that.y);
}

Maze::cell Maze::cell::commonWall(cell a, cell b)
{
	cell wall = { 0, 0 };
	if (abs(a.x - b.x) == 2 &&
		abs(a.y - b.y) == 0)
	{
		return{ a.y, (a.x + b.x) / 2 };
	}
	if (abs(a.y - b.y) == 2 &&
		abs(a.x - b.x) == 0)
	{
		return{ (a.y + b.y) / 2, a.x };
	}
	//Default 
	return{ 0, 0 };
}

LinkedList <Maze::cell> Maze::cell::getNeighbours(const int HEIGHT, const int WIDTH)
{
	LinkedList <cell> neighbours;
	if (exists(y - 2, x, HEIGHT, WIDTH)) neighbours.push_back({ y - 2, x });
	if (exists(y + 2, x, HEIGHT, WIDTH)) neighbours.push_back({ y + 2, x });
	if (exists(y, x + 2, HEIGHT, WIDTH)) neighbours.push_back({ y, x + 2 });
	if (exists(y, x - 2, HEIGHT, WIDTH)) neighbours.push_back({ y, x - 2 });
	return neighbours;
}