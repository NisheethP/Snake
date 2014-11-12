#include "headers.h"
#include "Constants.h"
#include "Board.h"
#include <boost\thread\thread.hpp>
#include <boost\ref.hpp>

const int snakeMoveFreq = 1000; //Snake moving frequency in milliseconds
const int boardUpdFreq = 200; //Board update frequency in milliseconds

using boost::ref;

//Move the snake in block in directio it is facing with frequency of 2.5Hz
void keepSnakeMoving(Board& board);

//Update the board (with frequency of 2.5 Hz) while keepUpdating is true
void updateScreen(Board& board, bool& keepUpdating);

//Checks for whether to keep the board updating
void checkUpdating(bool& isUpdating);

//Get user input in a loop in a separate thread.
void getUserInput(Board& board, bool& isUpdating, bool& isGettingInput);

//Set if the horizontal-blinking cursor is visible or not
void ShowConsoleCursor(bool showFlag);

//Terminate the game by setting all loop variables to false, and thus lead the thread to its end after detachment
void terminateGame(bool& isUpdating, bool& isGettgingInput, Board& board);

int main()
{
	SetDefaultColour();
	ShowConsoleCursor(false);

	Board mainBoard({1,1}, {5,5});
	bool isUpdating = true;
	bool isGettingInput = true;

	boost::thread InputLoop(ref(getUserInput), ref(mainBoard), ref(isUpdating), ref(isGettingInput));
	boost::thread MoveSnake(ref(keepSnakeMoving), ref(mainBoard));
	boost::thread BoardUpdate(ref(updateScreen), ref(mainBoard), ref(isUpdating));
		
	while (true)
	{
		Sleep(1000);
		char x = _getch();
		if (x == 'q' || x == 'Q')
		{
			terminateGame(isUpdating, isGettingInput, mainBoard);
			break;
		}
	}

	BoardUpdate.detach();
	MoveSnake.detach();
	InputLoop.detach();

	return 0;
}

//Set if the horizontal-blinking cursor is visible or not
void ShowConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(Global::hStdout, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(Global::hStdout, &cursorInfo);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~
//SEPARATE THREAD FUNCTIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~

//Move the snake in block in directio it is facing with frequency of 2.5Hz
void keepSnakeMoving(Board& board)
{
	while (board.getIsSnakeMoving())
	{
		Sleep(snakeMoveFreq);
		board.moveSnake();
	}
}

//Update the board (with frequency of 5 Hz) while keepUpdating is true
void updateScreen(Board& board, bool& keepUpdating)
{
	int i = 0;
	while (keepUpdating)
	{
		Sleep(boardUpdFreq);
		board.drawBoard();
	}
}

//Get user input in a loop in a separate thread.
void getUserInput(Board& board, bool& isUpdating, bool& isGettingInput)
{
	KeyPress key = Key_Other;
	KeyInput userInput;
	while (isGettingInput)
	{
		userInput = getArrowInput();
		
		if (userInput.isArrowKey)
		{
			switch (userInput.arrowKey)
			{
			case Key_Up:
				board.changeSnakeDirection(Dir_Up);
				break;
			case Key_Down:
				board.changeSnakeDirection(Dir_Down);
				break;
			case Key_Right:
				board.changeSnakeDirection(Dir_Right);
				break;
			case Key_Left:
				board.changeSnakeDirection(Dir_Left);
				break;
			default:
				break;
			}
		}

		else
		{
			if (char_To_KeyPress(key, userInput.keyNum))
			{
				switch (key)
				{
				case Key_Enter:
					terminateGame(isUpdating, isGettingInput, board);
				}
			}		
		}
	}	
}

void terminateGame(bool& isUpdating, bool& isGettgingInput, Board& board)
{
	isUpdating = false;
	isGettgingInput = false;
	board.stopSnakeMoving();
}