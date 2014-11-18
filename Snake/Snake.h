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


using TailVector = std::vector<SnakeTail>;

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

	int getLength() const;

	void setViewDir(Direction dir);
	
	Direction getViewDir() const;
	Direction getOppViewDir() const;

	void incLength();
};

#endif