#pragma once
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <Windows.h>
#include <conio.h>
enum Colour
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

enum KeyPress
{
	Key_Up,
	Key_Down,
	Key_Left,
	Key_Right,
	Key_Enter,
	Key_Other
};
struct keyInput
{
	int keyNum;
	KeyPress arrowKey;
	bool isArrowKey;
};

keyInput getArrowInput();

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

void ClearScreen();
int PressAnyKey(const char *prompt = "\n\nPress any key to continue . . .");
	
WORD ColourToFore(Colour);
WORD ColourToBack(Colour);

void SetDefaultColour(Colour pcolour = Colour::White);
void SetColour(Coord crd, int length, Colour fore = Colour::DarkBlue, Colour back = Colour::White);

int wherex();
int wherey();
void gotoxy(int column = wherex(), int line = wherey());

#endif