#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "Peg.h"
#include "Snake.h"
#include "Functions.h"
#include <utility>

class Bend
{
public:
	//Coordiante of the bend on the board
	Coord bendCoord;
	//Direction for the tail to go towards for
	Direction bendDir;
};

using PegLoc = std::pair<Peg*, Coord>;
using SnakeLoc = std::pair<Snake, Coord>;
using charVector2D = std::vector<std::vector<char>>;
using BoardPeg = std::vector<PegLoc>;

using BendVector = std::vector<Bend>;
using BendIter = BendVector::iterator;
using RevBendIter = BendVector::reverse_iterator;

//Converts Direction to Change in coordinates
Coord DirToNum(Direction pDir);

//Gives the Direction opposite to current direction
Direction oppDir(Direction pDir);

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

	bool isSnakeMoving;

	BendVector bends;

	//Returns the number in PEGS vector for given location in row, col
	int GetPegNum(int col, int row);

	//Sets the type of Peg in given location
	void setWall(int col, int row);
	void setSnakeTail(int col, int row);
	void setSnakeHead(int col, int row);
	void setFruit(int col, int row);
	void removePeg(int col,int row);

	void setWall(Coord crd);
	void setSnakeTail(Coord crd);
	void setSnakeHead(Coord crd);
	void setFruit(Coord crd);
	void removePeg(Coord crd);
public:
	Board(Coord pDeltaCoord, Coord pInitCoord);
	~Board();

	void spawnFruit();
	//Convert on screen coordinates to Array Coordinates or vice-versa
	Coord convCoords(Coord pCoord, bool isArrayCoord);
	

	Coord getDeltaCoord() const;
	Coord getInitCoord() const;
	int getNumFruits() const;
	bool getIsSnakeMoving() const;

	void stopSnakeMoving();

	//Draws the board on the output on the screen
	void drawBoard();

	//Updates the snake on the board
	void updateSnake();

	//Moves the snake; Friend to make it accessible to both [thread] and [Board]
	void moveSnake();
	
	//Changes the direction of motion of snake
	void changeSnakeDirection(Direction dir); 


};

#endif