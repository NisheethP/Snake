#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "SnakeHead.h"
#include "SnakeTail.h"
#include <vector>

typedef std::vector<SnakeTail> TailVector;

enum Direction
{
	Dir_Up,
	Dir_Bottom,
	Dir_Left,
	Dir_Right,
	Dir_Error
};

class Snake
{
private:
	int length;
	Direction viewDir;
	SnakeHead head;
	TailVector tail;
public:
	Snake();
	~Snake();

	void incLength();
};

#endif