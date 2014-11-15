#include "Snake.h"
#include "Board.h"

Snake::Snake() : 
length(20), 
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

//Adds a bend at [crd] Coordinate
bool  Snake::addBend(int Len, Coord crd)
{
	Bend tempBend(Len, crd);
	bends.push_back(tempBend);
	
	return true;
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
	/*
	if (bendNum >= bends.size())
		return false;
	else
	{
		bends[bendNum].first -= DirToNum(bends[bendNum].second);
	}
	*/
	return true;	
}

//Gets the queue that stores the bends in its entirety
BendVector& Snake::getAllBends()
{
	return bends;
}