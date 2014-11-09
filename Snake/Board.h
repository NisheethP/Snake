#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "Peg.h"
#include "Snake.h"
#include "Functions.h"
#include <utility>

typedef std::pair<Peg*,Coord> PegLoc;
typedef std::pair<Snake, Coord> SnakeLoc;
typedef std::vector<std::vector<char>> charVector2D;
typedef std::vector<PegLoc> BoardPeg;

class Board
{
private:
	BoardPeg Pegs;
	SnakeLoc snake;
	int numFruits;
	Coord deltaCoord;
	Coord initCoord;
	const static int ROW_NUM;
	const static int COL_NUM;

	//Returns the number in PEGS vector for given location in row, col
	int GetPegNum(int col, int row);

	//Sets the type of Peg in given location
	void setWall(int col, int row);
	void setSnakeTail(int col, int row);
	void setSnakeHead(int col, int row);
	void setFruit(int col, int row);
public:
	Board(Coord pDeltaCoord, Coord pInitCoord);
	~Board();

	void spawnFruit();
	//Convert on screen coordinates to Array Coordinates or vice-versa
	Coord convCoords(Coord pCoord, bool isArrayCoord);
	Coord DirToNum(Direction pDir);

	Coord getDeltaCoord();
	Coord getInitCoord();
	int getNumFruits();
	void drawBoard();
	
};

#endif