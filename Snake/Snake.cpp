#include "Snake.h"


Snake::Snake() : 
length(3), 
viewDir(Direction::Dir_Right),
tail(TailVector()),
bends(BendVector())
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

bool Snake::addBend(int len, Direction dir)
{
	if (len < length && dir != Dir_Error)
	{
		Bend tempBend(len, dir);
		bends.push_back(tempBend);
		return true;
	}
	else
		return false;
}

bool Snake::removeBend()
{
	if (!bends.empty())
	{
		bends.pop_back();
		return true;
	}
	return false;
}

Bend Snake::getBend(int num)
{
	if (num >= bends.size())
	{
		return bends.at(bends.size() - 1);
	}
	else
		return bends.at(num);
}