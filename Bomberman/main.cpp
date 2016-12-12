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
#include "SDL.h"
#include "graphics.h"



#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define FPS 60

int main(int argc, char* argv[])
{

	Game game;
	game.gameLoop();
	
	//_getch();
	
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
	return 0;
}

