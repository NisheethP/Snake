#include "Snake.h"
#include "Board.h"

Bend::Bend(int len, Direction dir) :
totLength(len), bendDir(dir), delCoord({0,0})
{
	delCoord.x = len * DirToNum(dir).x;
	delCoord.y = len * DirToNum(dir).y;
}

Snake::Snake() : 
length(20), 
viewDir(Direction::Dir_Right),
tail(TailVector()),
bends(BendVector())
{
	for (int i = tail.size(); i < length; i++)
		tail.push_back(SnakeTail());

	bends.push_back(Bend(6, Dir_Left));
	bends.push_back(Bend(3, Dir_Down));
}

Snake::~Snake()
{
}

void Snake::incLength()
{
	if (length <= 100)
		length++;
}

//Adds a bend
bool Snake::addBend(int Len, Direction dir)
{
	Bend tempBend(Len, dir);
	bends.push_back(tempBend);
	
	return true;
}

//Removes the last bend in the Snake (can't remove any intermediate bend afterall...)
//Its the first in the vector itself (EQUIVALENT TO POP_FRONT IN QUEUE)
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

Direction Snake::getOppViewDir() const
{
	return oppDir(viewDir);
}

void Snake::setViewDir(Direction dir)
{
	viewDir = dir;
}

//Moves all bends one backward. Shoudl be done one each movement
void Snake::moveBendBack()
{
	for (BendIter bend = bends.begin(); bend != bends.end(); ++bend)
	{
		bend->totLength++;
		if (bend->totLength > length)
			removeBend();
	}
}

//Gets the queue that stores the bends in its entirety
BendVector& Snake::getAllBends()
{
	return bends;
}