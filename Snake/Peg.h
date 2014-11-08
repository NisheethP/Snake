#pragma once
#ifndef _PEG_H_
#define _PEG_H_

#include "Functions.h"
#include "Constants.h"
class Peg
{
protected:
	Colour pegColour;
	char pegShape;
	//bool isSpawnable;
public:
	Peg(Colour pegColour = Colour::White, char pegShape = Constants::Empty);
	char get_pegShape();
	Colour get_pegColour();
	~Peg();
};

#endif