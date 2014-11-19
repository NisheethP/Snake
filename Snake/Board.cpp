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
isSnakeMoving(true),
bends(BendVector())
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
	Coord endTailCoord = snake.second;

	if (bends.empty())
	{
		Coord tempCoord = snake.second;
		for (int len = 0; len < snake.first.getLength(); len++)
		{
			tempCoord += DirToNum(snake.first.getOppViewDir());
			setSnakeTail(tempCoord); 
			endTailCoord = tempCoord;
		}
		endTailCoord += DirToNum(snake.first.getOppViewDir());
	}
	else
	{
		int bentLen = 0;
		Coord tempCoord = snake.second;
		RevBendIter prevBend = bends.rbegin();
		for (RevBendIter bendIter = bends.rbegin(); bendIter != bends.rend(); ++bendIter)
		{
			if (bendIter == bends.rbegin())
			{
				while (tempCoord != bendIter->bendCoord)
				{
					tempCoord += DirToNum(snake.first.getOppViewDir());
					setSnakeTail(tempCoord);
					bentLen++;
				}
			}
			else
			{
				Bend debugBend = *bendIter;
				Bend prevDebugBend = *prevBend;
				while (tempCoord != debugBend.bendCoord)
				{
					tempCoord += DirToNum(prevBend->bendDir);
					setSnakeTail(tempCoord);
					bentLen++;
				}				
				++prevBend;
			}
		}
		int remLen = snake.first.getLength() - bentLen;
		tempCoord = bends.at(0).bendCoord;
		for (int i = 0; i < remLen; i++)
		{
			tempCoord += DirToNum(bends.at(0).bendDir);
			setSnakeTail(tempCoord);
			endTailCoord = tempCoord;
		}

		endTailCoord += DirToNum(bends.at(0).bendDir);
	}

	removePeg(endTailCoord);
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
}

//Changes the direction of motion of snake
void Board::changeSnakeDirection(Direction dir)
{
	if (oppDir(dir) != snake.first.getViewDir() && dir != snake.first.getViewDir())
	{
		addBend(snake.second, snake.first.getOppViewDir());
		snake.first.setViewDir(dir);
	}
}

//Adds a bend at the given coordinates
bool Board::addBend(Coord crd, Direction Dir)
{
	if (crd.x < COL_NUM && crd.y < ROW_NUM && crd.x > 0 && crd.y > 0)
	{
		bends.push_back({ crd, Dir });
		return true;
	}
	return false;
}

//Remove the last bend (first to be added in vector)
//Equivalent to the pop_fornt funciton in a queue, but vector is random accesible and interator safe
bool Board::removeBend()
{
	if (bends.empty())
		return false;

	BendVector::iterator bendIter = bends.begin();
	bendIter++;
	BendVector tempBends;
	for (bendIter; bendIter != bends.end(); ++bendIter)
	{
		tempBends.push_back(*bendIter);
	}

	bends.clear();
	bends = tempBends;
	return true;
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