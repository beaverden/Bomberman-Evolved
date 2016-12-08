// PixelRPG.cpp : Defines the entry point for the console application.
//


#include "Queue.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Maze.h"
#include "Stack.h"
#include <windows.h>
#include "ConsoleOutput.h"
//#include <d2d1.h>
//#pragma comment(lib, "d2d1")


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void SetColor(int ForgC)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ForgC);
	return;
}

int main()
{

	int height = 17,
		width = 51;
	Maze maze(height, width);
	char board[Maze::MAX_MAZE_HEIGHT][Maze::MAX_MAZE_WIDTH];
	maze.generateMaze(board);
	Stack <Maze::cell> st;

	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			char c;
			unsigned short color;
			switch (board[i][j])
			{
			case -1: { c = '@'; color = 7; } break;
			case 0: { c = ' '; color = 0; } break;
			case 1: { c = '+';  color = 4; } break;
			}
			ConsoleOutput::printChar(c, color);
		}
		printf("\n");
	}
	while (true)
	{
		int c = _getch();
		if (c == KEY_UP)
		{
			ConsoleOutput::setCursorAt(0, 0);
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					char c;
					unsigned short color;
					switch (board[i][j])
					{
					case -1: { c = '@'; color = 7; } break;
					case 0: { c = ' '; color = 0; } break;
					case 1: { c = '+';  color = 4; } break;
					}
					ConsoleOutput::printChar(c, color);
				}
				printf("\n");
			}
		}
	}
	_getch();
	
	/*
		st = maze.calculatePath(board, { posY, posX }, { height - 2, width - 2 });
		st.iterator();

		while (!st.isNull())
		{
			board[st.curr().y][st.curr().x] = 1;
			st.next();
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (i == posY && j == posX) { printf("O"); continue; }
				//SetColor(15);
				switch (board[i][j])
				{
				case -1: printf("@"); break;
				case 0: printf(" "); break;
				case 1: { SetColor(5);  printf("+");  SetColor(15); } break;
				}
			}
			printf("\n");
		}
		st.iterator();
		while (!st.isNull())
		{
			board[st.curr().y][st.curr().x] = 0;
			st.next();
		}

	}
	*/

	/*
	while (0)
	{
	int key = 0;
	key = _getch();

	if (key == KEY_UP)
	{
	player.move(-1, 0);
	}
	else if (key == KEY_DOWN)
	{
	player.move(1, 0);
	}
	else if (key == KEY_RIGHT)
	{
	player.move(0, 1);
	}
	else if (key == KEY_LEFT)
	{
	player.move(0, -1);
	}
	else
	{
	continue;
	}

	system("cls");

	int posX = player.getPosX();
	int posY = player.getPosY();
	if (posX == 9)
	{
	player.setPosX(0);
	}
	if (posY == 9)
	{
	player.setPosY(0);
	}

	//printf("%d %d\n", posY, posY);
	for (int i = 0; i < 10; i++)
	{
	for (int j = 0; j < 10; j++)
	{
	if (i == posX && j == posY)
	{
	printf("*");
	}
	else
	{
	printf(".");
	}
	}
	printf("\n");
	}

	}
	*/
	return 0;
}

