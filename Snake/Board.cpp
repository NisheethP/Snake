#include "Board.h"


Board::Board(Coord pDeltaCoord):
deltaCoord(pDeltaCoord),
numFruits(0)
{
}

Board::~Board()
{
}

Coord Board::convCoords(Coord pCoord, bool isArrayCoord)
{
	Coord tempCoord = {0,0};
	if (isArrayCoord)
	{
		Coord rCoord = { 0, 0 };

		rCoord.x = pCoord.x - initCoord.x;
		rCoord.x /= deltaCoord.x;

		rCoord.y = pCoord.y - initCoord.y;
		rCoord.y /= deltaCoord.y;

	}
	else
	{
		Coord rCoord = { 0, 0 };

		rCoord.x = deltaCoord.x * pCoord.x + initCoord.x;

		rCoord.y =  deltaCoord.y * pCoord.y + initCoord.y;

	}
}


Coord Board::getDeltaCoord()
{
	return deltaCoord;
}


Coord Board::getInitCoord()
{
	return initCoord;
}


int Board::getNumFruits()
{
	return numFruits;
}


void Board::drawBoard()
{
}
