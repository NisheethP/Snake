#pragma once
#ifndef _PEG_H_
#define _PEG_H_

#include "Functions.h"
#include "Constants.h"

enum PegType
{
	BasePeg,
	FruitPeg,
	SnakeTailPeg,
	SnakeHeadPeg,
	WallPeg
};

class Peg
{
protected:
	Colour pegColour;
	char pegShape;
	//bool isSpawnable;
	PegType pegType;
public:
	
	Peg(Colour pegColour = Colour::White, char pegShape = Constants::Empty);
	char get_pegShape() const;
	Colour get_pegColour() const;
	PegType getPegType() const;
	~Peg();
};

#endif