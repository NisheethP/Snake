#include "Snake.h"


Snake::Snake() : 
length(12), 
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
		bends.pop_front();
		return true;
	}
	return false;
}

Bend Snake::getBend(int num)
{
	if (num >= bends.size() )
	{
		return bends.back();
	}
	else
	{
		return bends[num];
	}
}

int Snake::getLength()
{
	return length;
}

int Snake::getBendNum()
{
	return bends.size();
}

Direction Snake::getViewDir()
{
	return viewDir;
}

void Snake::setViewDir(Direction dir)
{
	viewDir = dir;
}

bool Snake::moveBendBack(int bendNum)
{
	if (bendNum >= bends.size())
		return false;
	else
	{
		bends[bendNum].first += 1;
		if (bends[bendNum].first > length)
			removeBend();
	}
	return true;	
}