#include "ConsoleOutput.h"
#include <windows.h>
#include <iostream>

ConsoleOutput::ConsoleOutput()
{
}


ConsoleOutput::~ConsoleOutput()
{
}

void ConsoleOutput::cls()
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}

void ConsoleOutput::setCursorAt(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void ConsoleOutput::setColor(unsigned short colour)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	SetConsoleTextAttribute(hOut, colour);
}

void ConsoleOutput::printChar(char data, unsigned short color)
{
	setColor(color);
	printf("%c", data);
}

void ConsoleOutput::setChar(int x, int y, char data, unsigned short color)
{
	setCursorAt(x, y);
	setColor(color);
	printf("%c", data);
}

