#pragma once
class ConsoleOutput
{
public:
	static const unsigned short BLACK = 0;
	static const unsigned short BLUE = 1;
	static const unsigned short GREEN = 2;
	static const unsigned short CYAN = 3;
	static const unsigned short RED = 4;
	static const unsigned short PURPLE = 5;
	static const unsigned short YELLOW = 6;
	static const unsigned short WHITE = 7;
	static const unsigned short GRAY = 8;

	ConsoleOutput();
	~ConsoleOutput();

	static void cls();
	static void setCursorAt(int, int);
	static void setColor(unsigned short);
	static void printChar(char, unsigned short);
	static void setChar(int, int, char, unsigned short);

	/*
		@param color (given static constants from [0, 8]
		@param brightness {0, 1}
		@param background (given static constants from [0, 8])
		@return respective color with the given brightness and background
	*/
	static unsigned short getColor(unsigned short, int, int);
};

