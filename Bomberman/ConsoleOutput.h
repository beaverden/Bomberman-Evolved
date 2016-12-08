#pragma once
class ConsoleOutput
{
public:
	const unsigned short BLUE = 1;
	const unsigned short GREEN = 2;
	const unsigned short CYAN = 3;
	const unsigned short RED = 4;
	const unsigned short PURPLE = 5;
	const unsigned short YELLOW = 6;
	const unsigned short WHITE = 7;
	const unsigned short GRAY = 8;

	ConsoleOutput();
	~ConsoleOutput();

	static void cls();
	static void setCursorAt(int, int);
	static void setColor(unsigned short);
	static void printChar(char, unsigned short);
	static void setChar(int, int, char, unsigned short);
};

