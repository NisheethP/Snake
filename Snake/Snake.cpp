#include "Snake.h"


Snake::Snake() : 
length(3), 
viewDir(Direction::Dir_Right),
tail(TailVector(0))
{
	for (int i = tail.size(); i < length; i++)
		tail.push_back(SnakeTail());
}


Snake::~Snake()
{
}

void Snake::incLength()
{
	if (length <= 100)
		length++;
}
