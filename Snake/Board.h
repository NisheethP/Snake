#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "Peg.h"
#include "Snake.h"
#include "Functions.h"

typedef std::vector<Peg*> PegVector;
typedef std::vector<std::vector<char>> charVector2D;

class Board
{
private:
	PegVector Pegs;
	int numFruits;
	Coord deltaCoord;
	Coord initCoord;
public:
	Board(Coord pDeltaCoord);
	~Board();

	void spawnFruit();

	Coord convCoords(Coord pCoord, bool isArrayCoord);

	Coord getDeltaCoord();
	Coord getInitCoord();
	int getNumFruits();
	void drawBoard();
};

#endif