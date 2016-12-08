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
#include "Game.h"
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

	Game game;
	game.initLevel(17, 45);
	game.printBoard();
	//ConsoleOutput::setChar(5, 10, '@', 4);
	while (true)
	{
		int key = 0;
		key = _getch();

		if (key == KEY_UP)
		{
			game.movePlayer(-1, 0);
		}
		else if (key == KEY_DOWN)
		{
			game.movePlayer(1, 0);
		}
		else if (key == KEY_RIGHT)
		{
			game.movePlayer(0, 1);
		}
		else if (key == KEY_LEFT)
		{
			game.movePlayer(0, -1);
		}
		else
		{
			continue;
		}
		game.printBoard();
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

