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
	//Length between two consequtive bends in the tail
	int secLength;
	//Change in coordinate of bend with respect to previous bend
	Coord delCoord;

	Bend(int len = 0, Coord crd = {0,0}) :
		secLength(len), delCoord(crd)
	{}
};

using TailVector = std::vector<SnakeTail>;
using BendVector = std::vector<Bend>;

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

	//Moves bend number bendNum one backward. Shoudl be done one each movement
	bool moveBendBack(int bendNum);

	void setViewDir(Direction dir);
	Direction getViewDir() const;

	void incLength();
	//Adds a bend at [crd] Coordinate
	bool addBend(int Len, Coord crd);
	
	//Removes the last bend in the Snake (can't remove any intermediate bend afterall...)
	bool removeBend();

	//Gets the [num] bend in the dequeue by iterating over
	Bend getBend(int num) const;

	//Gets the queue that stores the bends in its entirety
	BendVector& getAllBends();
};

#endif