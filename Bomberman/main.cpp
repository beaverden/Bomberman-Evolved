// PixelRPG.cpp : Defines the entry point for the console application.
//


#include "Queue.h"
#include "Stack.h"
#include "Vector.h"

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Maze.h"

#include "Game.h"
#include "SDL.h"
#include "graphics.h"
#include <string>
#include <fstream>
#include "Sprite.h"
#include "SpriteGroup.h"

#include <vector>
#include <time.h>
#include <cstdlib>
#include "SDL_Image.h"
#include "SDL_Mixer.h"


using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define FPS 60


class A
{
public:
	A()
	{
		p = new int;
		*p = 5;
	}
	~A()
	{
		delete p;
	}
	int * p;
};

class B
{
public:
	A a;
};

int main(int argc, char* argv[])
{

	Game game;
	game.gameLoop();
	B b;
	if (b.a.p)
	{
		printf("Heya %d", *(b.a.p));
	}
	_getch();

	return 0;
}

