#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "SnakeHead.h"
#include "SnakeTail.h"
#include "Functions.h"
#include <vector>


enum Direction
{
	Dir_Up,
	Dir_Down,
	Dir_Left,
	Dir_Right,
	Dir_Error
};

class Bend
{
	public:
	//Length from head of snake
	int totLength;
	//Change in coordinate of bend with respect to previous bend
	Coord delCoord;
	Direction bendDir;

	Bend(int len = 0, Coord crd = {0,0}, Direction dir = Dir_Right) :
		totLength(len), delCoord(crd), bendDir(Dir_Right)
	{}
};

using TailVector = std::vector<SnakeTail>;
using BendVector = std::vector<Bend>;
using BendIter = BendVector::iterator;
using RevBendIter = BendVector::reverse_iterator;

class Snake
{
private:
	int length;
	Direction viewDir;
	SnakeHead head;
	TailVector tail;
	//Direction of bend is the direction the snake was going in before the turn
	BendVector bends;

public:
	Snake();
	~Snake();

	int getLength() const;
	int getBendNum() const;

	//Moves all bends one backward. Shoudl be done one each movement
	bool moveBendBack();

	void setViewDir(Direction dir);
	Direction getViewDir() const;

	void incLength();
	//Adds a bend
	bool addBend(int Len, Coord crd, Direction dir);
	
	//Removes the last bend in the Snake (can't remove any intermediate bend afterall...)
	//Its the first in the vector itself (EQUIVALENT TO POP_FRONT IN QUEUE)
	bool removeBend();

	//Gets the [num] bend in the dequeue by iterating over
	Bend getBend(int num) const;

	//Gets the queue that stores the bends in its entirety
	BendVector& getAllBends();
};

#endif