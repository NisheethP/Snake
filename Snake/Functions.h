#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <Windows.h>

enum colour
{
	Gray,
	White,
	DarkRed,
	Red,
	DarkBlue,
	Blue,
	DarkGreen,
	Green,
	DarkCyan,
	Cyan,
	DarkMagenta,
	Magenta,
	DarkYellow,
	Yellow,
	None
};

struct Global
{
	static HANDLE hStdin;
	static HANDLE hStdout;
};

class Coord
{
public:
	int x;
	int y;

	Coord()
	{
		x = 0;
		y = 0;
	};

	Coord(int X, int Y)
	{
		x = X;
		y = Y;
	}

	bool operator== (Coord p_Coord)
	{
		return (p_Coord.x == this->x) && (p_Coord.y == this->y);
	}

	bool operator!= (Coord p_Coord)
	{
		return (p_Coord.x != this->x) && (p_Coord.y != this->y);
	}
};

int PressAnyKey(const char *prompt = "\n\nPress any key to continue . . .");
	
WORD ColourToFore(colour);
WORD ColourToBack(colour);

void SetDefaultColour(colour colour = colour::White);
void SetColour(Coord crd, int length, colour fore = colour::DarkBlue, colour back = colour::White);

int wherex();
int wherey();
void gotoxy(int column = wherex(), int line = wherey());

#endif