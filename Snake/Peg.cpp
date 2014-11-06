#include "Peg.h"


Peg::Peg(Colour p_pegColour, char p_pegShape) :
pegColour(p_pegColour),
pegShape(p_pegShape)
{
}


Peg::~Peg()
{

}

char Peg::get_pegShape()
{
	return pegShape;
}

Colour Peg::get_pegColour()
{
	return pegColour;
}
