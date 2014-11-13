#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "SnakeHead.h"
#include "SnakeTail.h"
#include <vector>

enum Direction
{
	Dir_Up,
	Dir_Down,
	Dir_Left,
	Dir_Right,
	Dir_Error
};

typedef std::vector<SnakeTail> TailVector;
typedef std::pair<int, Direction> Bend;
typedef std::vector<Bend> BendVector;

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
	//Adds a bend at [len] distance from the Head and the tail is pointing in [dir] behind the bend
	bool addBend(int len, Direction dir);
	
	//Removes the last bend in the Snake (can't remove any intermediate bend afterall...)
	bool removeBend();

	//Gets the [num] bend in the dequeue by iterating over
	Bend getBend(int num) const;

	//Gets the queue that stores the bends in its entirety
	BendVector& getAllBends();
};

#endif