#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "SnakeHead.h"
#include "SnakeTail.h"
#include <vector>

typedef std::vector<SnakeTail> TailVector;

enum Direction
{
	Top,
	Bottom,
	Left,
	Right,
	ERROR
};

class Snake
{
public:
	Snake();
	~Snake();
private:
	int length;
	Direction viewDir;
	SnakeHead head;
	TailVector tail;
};

#endif