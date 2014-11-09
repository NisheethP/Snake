#include "Peg.h"


Peg::Peg(Colour p_pegColour, char p_pegShape) :
pegColour(p_pegColour),
pegShape(p_pegShape),
pegType(PegType::BasePeg)
{
}


Peg::~Peg()
{

}

char Peg::get_pegShape() const
{
	return pegShape;
}

Colour Peg::get_pegColour() const
{
	return pegColour;
}

PegType Peg::getPegType() const
{
	return pegType;
}