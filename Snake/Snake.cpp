#include "Snake.h"
#include "Board.h"

Snake::Snake() : 
length(20), 
viewDir(Direction::Dir_Right),
tail(TailVector())
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

int Snake::getLength() const
{
	return length;
}

Direction Snake::getViewDir() const
{
	return viewDir;
}

Direction Snake::getOppViewDir() const
{
	return oppDir(viewDir);
}

void Snake::setViewDir(Direction dir)
{
	viewDir = dir;
}