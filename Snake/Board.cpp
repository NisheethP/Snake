#include <iostream>
#include <Windows.h>

#include "Board.h"
#include "Fruit.h"
#include "SnakeHead.h"
#include "SnakeTail.h"
#include "Wall.h"
#include <mutex>

using std::cout;

const int Board::ROW_NUM = 50;
const int Board::COL_NUM = 70;

Board::Board(Coord pDeltaCoord, Coord pInitCoord):
deltaCoord(pDeltaCoord),
initCoord(pInitCoord),
numFruits(0),
Pegs(ROW_NUM*COL_NUM, PegLoc(new Peg, { 0,0 })),
snake(SnakeLoc(Snake(), Coord(COL_NUM*0.5, ROW_NUM*0.5))),
isSnakeMoving(true)
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

	updateSnake();


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

Coord Board::getDeltaCoord() const
{
	return deltaCoord;
}

Coord Board::getInitCoord() const
{
	return initCoord;
}

int Board::getNumFruits() const
{
	return numFruits;
}

bool Board::getIsSnakeMoving() const
{
	return isSnakeMoving;
}

void Board::drawBoard()
{
	updateSnake();
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
void Board::removePeg(int row, int col)
{
	int num = GetPegNum(row, col);
	if (num >= Pegs.size())
		cout << "ERROR IN SIZE";
	else
	{
		delete Pegs[num].first;
		Pegs[num].first = new Peg();
	}
}

void Board::setWall(Coord crd)
{
	setWall(crd.y, crd.x);
}
void Board::setSnakeTail(Coord crd)
{
	setSnakeTail(crd.y, crd.x);
}
void Board::setSnakeHead(Coord crd)
{
	setSnakeHead(crd.y, crd.x);
}
void Board::setFruit(Coord crd)
{
	setFruit(crd.y, crd.x);
}
void Board::removePeg(Coord crd)
{
	removePeg(crd.y, crd.x);
}

void Board::stopSnakeMoving()
{
	isSnakeMoving = false;
}

//Updates the snake on the board
void Board::updateSnake()
{
	setSnakeHead(snake.second.y, snake.second.x);
	Coord tailEndCoord = snake.second;
	
	if (snake.first.getBendNum() > 0)
	{
		Coord tempCoord = snake.second;
		Coord nextBendCoord = snake.second;
	
		for (RevBendIter curBend = snake.first.getAllBends().rbegin(); curBend != snake.first.getAllBends().rend(); ++curBend)
		{
			nextBendCoord += curBend->delCoord;
			while (tempCoord != nextBendCoord)
			{
				Direction debugBend = curBend->bendDir;
				tempCoord += DirToNum(debugBend);
				setSnakeTail(tempCoord);
			}
			//tempCoord = curBend->delCoord;
		}
	}

	else
	{
		Coord tempCoord = snake.second;
		for (int len = 0; len < snake.first.getLength(); len++)
		{
			tempCoord += DirToNum(snake.first.getOppViewDir());
			setSnakeTail(tempCoord);
			tailEndCoord = tempCoord;
		}
		tailEndCoord += DirToNum(snake.first.getOppViewDir());

	}

	int tempPegNum = GetPegNum(tailEndCoord.y, tailEndCoord.x);
	if (Pegs[tempPegNum].first->getPegType() == PegType::SnakeTailPeg)
	{
		removePeg(tailEndCoord);
	}
}

//Moves the Snake
void Board::moveSnake()
{
	Coord tempCoord = { 0, 0 };
	tempCoord.x = DirToNum(snake.first.getViewDir()).x;
	tempCoord.y = DirToNum(snake.first.getViewDir()).y;

	PegType pegType = Pegs[GetPegNum(snake.second.y + tempCoord.y, snake.second.x + tempCoord.x)].first->getPegType();
	if (pegType == PegType::BasePeg || pegType == PegType::FruitPeg)
	{
		snake.second.x += tempCoord.x;
		snake.second.y += tempCoord.y;
	}

	snake.first.moveBendBack();
}

//Changes the direction of motion of snake
void Board::changeSnakeDirection(Direction dir)
{
	if (oppDir(dir) != snake.first.getViewDir() && dir != snake.first.getViewDir())
	{
		//snake.first.addBend(0, snake.first.getViewDir());
		snake.first.setViewDir(dir);
	}
}

//Converts Direction to change in coordinate
Coord DirToNum(Direction pDir)
{
	Coord rCoord = { 0, 0 };
	switch (pDir)
	{
	case Dir_Right:
		rCoord.x = 1;
		break;
	case Dir_Left:
		rCoord.x = -1;
		break;
	case Dir_Down:
		rCoord.y = 1;
		break;
	case Dir_Up:
		rCoord.y = -1;
		break;
	case Dir_Error:
	default:
		break;
	}

	return rCoord;
}

//Gives the Direction opposite to current direction
Direction oppDir(Direction pDir)
{
	Direction rDir;
	switch (pDir)
	{
	case Dir_Right:
		rDir = Dir_Left;
		break;
	case Dir_Left:
		rDir = Dir_Right;
		break;
	case Dir_Down:
		rDir = Dir_Up;
		break;
	case Dir_Up:
		rDir = Dir_Down;
		break;
	case Dir_Error:
	default:
		break;
	}

	return rDir;
}
