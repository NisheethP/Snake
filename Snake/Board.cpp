#include "Board.h"
#include <iostream>

#include "Fruit.h"
#include "SnakeHead.h"
#include "SnakeTail.h"
#include "Wall.h"

using std::cout;

const int Board::ROW_NUM = 40;
const int Board::COL_NUM = 60;

Board::Board(Coord pDeltaCoord, Coord pInitCoord):
deltaCoord(pDeltaCoord),
initCoord(pInitCoord),
numFruits(0),
Pegs(ROW_NUM*COL_NUM, PegLoc(new Peg, { 0,0 }))
{
	for (int i = 0; i < ROW_NUM*COL_NUM; i++)
	{
		Pegs[i].second.x = i % COL_NUM;
		Pegs[i].second.y = i / COL_NUM;
	}

	for (int i = 0; i < Pegs.size(); i++)
	{
		Pegs[i].first = new Peg();
	}

	for (int row = 0; row < ROW_NUM; row++)
	{
		for (int col = 0; col < COL_NUM; col++)
		{	
			if (row == 0 || row == ROW_NUM-1 || col == 0 || col == COL_NUM-1)
				setWall(row, col);
		}
	}

	/*
	 * This will spawn the snake on the screen.
	 * By default, the snake spawn position will be:
	 * COL/2, ROW/2 for HEAD
	 * 3 TAILS in negative-X direction (left)
	 * Thus, it will spawn with looking towards RIGHT 
	 */


}

Board::~Board()
{
	for (int i = 0; i < Pegs.size(); i++)
	{
		delete Pegs[i].first;
	}
}

//Convert on screen coordinates to Array Coordinates or vice-versa
Coord Board::convCoords(Coord pCoord, bool isArrayCoord)
{
	Coord tempCoord = {0,0};
	if (isArrayCoord)
	{
		tempCoord.x = pCoord.x - initCoord.x;
		tempCoord.x /= deltaCoord.x;

		tempCoord.y = pCoord.y - initCoord.y;
		tempCoord.y /= deltaCoord.y;

	}
	else
	{
		tempCoord.x = deltaCoord.x * pCoord.x + initCoord.x;
		tempCoord.y = deltaCoord.y * pCoord.y + initCoord.y;

	}
	return tempCoord;
}


Coord Board::getDeltaCoord()
{
	return deltaCoord;
}


Coord Board::getInitCoord()
{
	return initCoord;
}


int Board::getNumFruits()
{
	return numFruits;
}


void Board::drawBoard()
{
	Coord curCoord = this->initCoord;
	int PegNum = 0;
	for (int colIter= 0; colIter < COL_NUM; colIter++)
	{
		for (int rowIter = 0; rowIter < ROW_NUM; rowIter++)
		{
			curCoord = { initCoord.y + colIter*deltaCoord.y, initCoord.x + rowIter*deltaCoord.x };
			gotoxy(curCoord.x, curCoord.y);
			PegNum = GetPegNum(rowIter, colIter);
			cout << Pegs[PegNum].first->get_pegShape();
		}
	}
}

//Returns the number in PEGS vector for given location in row, col
int Board::GetPegNum(int row, int col)
{
	int num = row*COL_NUM + col;
	if (num >= Pegs.size())
		return 0;

	if (Pegs[num].second == Coord(col, row))
		return num;
	
	else 
		return 0;
}

//Sets the type of Peg in given location
void Board::setWall(int row, int col)
{
	int num = GetPegNum(row, col);
	if (num >= Pegs.size())
		cout << "ERROR IN SIZE";
	else
	{
		delete Pegs[num].first;
		Pegs[num].first = new Wall();
	}
}
void Board::setSnakeTail(int row, int col)
{
	int num = GetPegNum(row, col);
	if (num >= Pegs.size())
		cout << "ERROR IN SIZE";
	else
	{
		delete Pegs[num].first;
		Pegs[num].first = new SnakeTail();
	}
}
void Board::setSnakeHead(int row, int col)
{
	int num = GetPegNum(row, col);
	if (num >= Pegs.size())
		cout << "ERROR IN SIZE";
	else
	{
		delete Pegs[num].first;
		Pegs[num].first = new SnakeHead();
	}
}
void Board::setFruit(int row, int col)
{
	int num = GetPegNum(row, col);
	if (num >= Pegs.size())
		cout << "ERROR IN SIZE";
	else
	{
		delete Pegs[num].first;
		Pegs[num].first = new Fruit();
	}
}