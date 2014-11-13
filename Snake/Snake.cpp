#include "Snake.h"


Snake::Snake() : 
length(12), 
viewDir(Direction::Dir_Right),
tail(TailVector()),
bends(BendVector())
{
	for (int i = tail.size(); i < length; i++)
		tail.push_back(SnakeTail());

	bends.push_back(Bend(6, Dir_Right));
	bends.push_back(Bend(3, Dir_Up));
}

Snake::~Snake()
{
}

void Snake::incLength()
{
	if (length <= 100)
		length++;
}

//Adds a bend at [len] distance from the Head and the tail is pointing in [dir] behind the bend
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

//Removes the last bend in the Snake (can't remove any intermediate bend afterall...)
bool Snake::removeBend()
{
	if (bends.empty())
		return false;

	BendVector::iterator bendIter = bends.begin();
	bendIter++;
	BendVector tempBends;
	for (bendIter; bendIter != bends.end(); ++bendIter)
	{
		tempBends.push_back(*bendIter);
	}

	bends.clear();
	bends = tempBends;
	return true;
}

//Gets the [num] bend in the dequeue by iterating over
Bend Snake::getBend(int num) const
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

int Snake::getLength() const
{
	return length;
}

int Snake::getBendNum() const
{
	return bends.size();
}

Direction Snake::getViewDir() const
{
	return viewDir;
}

void Snake::setViewDir(Direction dir)
{
	viewDir = dir;
}

//Moves bend number bendNum one backward. Shoudl be done one each movement
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

//Gets the queue that stores the bends in its entirety
BendVector& Snake::getAllBends()
{
	return bends;
}