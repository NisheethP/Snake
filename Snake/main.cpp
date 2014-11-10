#include "headers.h"
#include "Constants.h"
#include "Board.h"
#include <boost\thread\thread.hpp>
#include <boost\ref.hpp>

using boost::ref;

//Move the snake in block in directio it is facing with frequency of 2.5Hz
void keepSnakeMoving(Board& board);

//Update the board (with frequency of 2.5 Hz) while keepUpdating is true
void updateScreen(Board& board, bool keepUpdating = true);

//Checks for whether to keep the board updating
void checkUpdating(bool& isUpdating);

//Set if the horizontal-blinking cursor is visible or not
void ShowConsoleCursor(bool showFlag);

int main()
{
	SetDefaultColour();
	ShowConsoleCursor(false);

	Board mainBoard({1,1}, {5,5});
	bool isUpdating = true;

	boost::thread MoveSnake(ref(keepSnakeMoving), ref(mainBoard));
	boost::thread BoardUpdate(ref(updateScreen), ref(mainBoard), ref(isUpdating));
	boost::thread CheckBoardUpdate(checkUpdating, ref(isUpdating));

	MoveSnake.join();
	BoardUpdate.join();
	CheckBoardUpdate.join();

	PressAnyKey();
	return 0;
}

//Move the snake in block in directio it is facing with frequency of 2.5Hz
void keepSnakeMoving(Board& board)
{
	while (board.getIsSnakeMoving())
	{
		Sleep(400);
		board.moveSnake();
	}
}

//Update the board (with frequency of 5 Hz) while keepUpdating is true
void updateScreen(Board& board, bool keepUpdating)
{
	while (keepUpdating)
	{
		Sleep(200);
		board.drawBoard();
	}
}

//Set if the horizontal-blinking cursor is visible or not
void ShowConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(Global::hStdout, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(Global::hStdout, &cursorInfo);
}

//Checks for whether to keep the board updating
void checkUpdating(bool& isUpdating)
{
	_getch();
	isUpdating = false;
}