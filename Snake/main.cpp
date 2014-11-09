#include "headers.h"
#include "Constants.h"
#include "Board.h"
int main()
{
	SetDefaultColour();
	Board mainBoard({1,1}, {5,5});
	mainBoard.drawBoard(); 
	PressAnyKey();
	return 0;
}