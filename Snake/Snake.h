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
	BendVector bends;

public:
	Snake();
	~Snake();

	void incLength();
	//Adds a bend at [len] distance from the Head and the tail is pointing in [dir] behind the bend
	bool addBend(int len, Direction dir);
	
	//Removes the last bend in the Snake (can't remove any intermediate bend afterall...)
	bool removeBend();

	//Gets the [num] bend in the stack by iterating over
	Bend getBend(int num);
};

#endif