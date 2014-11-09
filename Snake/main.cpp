#include "headers.h"
#include "Constants.h"
#include "Board.h"
#include <thread>

void *func();
int main()
{
	SetDefaultColour();
	Board mainBoard({1,1}, {5,5});

	//std::thread snake_board(moveSnake, mainBoard);
	mainBoard.drawBoard();
	_getch();
	moveSnake(mainBoard);
	mainBoard.drawBoard();
	
	
	PressAnyKey();
	return 0;
}