#include"BoardSetup.h"

#include <iostream>
#include <string>

//The following is a default constructor that will setup the normal board for beginning a game of chess
BoardSetup::BoardSetup() {
	board[0][0] = "White Rook";
	board[1][0] = "White Knight";
	board[2][0] = "White Bishop";
	board[3][0] = "White Queen";
	board[4][0] = "White King";
	whiteKingXPosition = 4;
	whiteKingYPosition = 0;
	board[5][0] = "White Bishop";
	board[6][0] = "White Knight";
	board[7][0] = "White Rook";

	for (int i = 0; i < 8; i++)
	{
		board[i][1] = "White Pawn";
	}

	for (int y = 2; y < 6; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[x][y] = "Empty";
		}
	}

	for (int i = 0; i < 8; i++)
	{
		board[i][6] = "Black Pawn";
	}

	board[0][7] = "Black Rook";
	board[1][7] = "Black Knight";
	board[2][7] = "Black Bishop";
	board[3][7] = "Black Queen";
	board[4][7] = "Black King";
	blackKingXPosition = 4;
	blackKingYPosition = 7;
	board[5][7] = "Black Bishop";
	board[6][7] = "Black Knight";
	board[7][7] = "Black Rook";

	player1sTurn = true;

}

//The following is a constructor that will take in a FEN and create a board from it.
BoardSetup::BoardSetup(string fen) {
	//This first point finds where hashes occur in the FEN so we can split up the pieces by row later.
	int findForwardSlashPostion = 0;
	int forwardSlashPositions[9];
	forwardSlashPositions[0] = -2;


	for (int i = 1; i < 8; i++) {
		findForwardSlashPostion = fen.find_first_of("/", findForwardSlashPostion + 1);
		forwardSlashPositions[i] = findForwardSlashPostion;
	}
	forwardSlashPositions[8] = (fen.find_first_of(" ", forwardSlashPositions[7]));



	string tempBoard[8][8];
	int xPositionCounter = 0;
	int yPositionCounter = 7;
	int counter = 0;
	int fenTracker = 1;
	//The following generates FEN in the array

	while (counter < forwardSlashPositions[8]) {
		if (forwardSlashPositions[fenTracker] == counter) {
			xPositionCounter = 0;
			yPositionCounter = yPositionCounter - 1;
			fenTracker = fenTracker + 1;
		}
		else {
			tempBoard[xPositionCounter][yPositionCounter] = fen.at(counter);
			xPositionCounter = xPositionCounter + 1;
		}
		counter = counter + 1;
	}

	for (int y = 7; y > -1; y--) {
		for (int x = 0; x < 8; x++) {
			board[x][y] = tempBoard[x][y];
		}
	}

	//The following code will convert the FEN in the board array by checking each square and converting from FEN into my version of chess representation.
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {

			if (board[x][y] == "r") {
				board[x][y] = "Black Rook";
			}
			else if (board[x][y] == "n") {
				board[x][y] = "Black Knight";
			}
			else if (board[x][y] == "b") {
				board[x][y] = "Black Bishop";
			}
			else if (board[x][y] == "q") {
				board[x][y] = "Black Queen";
			}
			else if (board[x][y] == "k") {
				board[x][y] = "Black King";
				blackKingXPosition = x;
				blackKingYPosition = y;
			}
			else if (board[x][y] == "p") {
				board[x][y] = "Black Pawn";
			}
			else if (board[x][y] == "R") {
				board[x][y] = "White Rook";
			}
			else if (board[x][y] == "N") {
				board[x][y] = "White Knight";
			}
			else if (board[x][y] == "B") {
				board[x][y] = "White Bishop";
			}
			else if (board[x][y] == "Q") {
				board[x][y] = "White Queen";
			}
			else if (board[x][y] == "K") {
				board[x][y] = "White King";
				whiteKingXPosition = x;
				whiteKingYPosition = y;
			}
			else if (board[x][y] == "P") {
				board[x][y] = "White Pawn";
			}
			else if (board[x][y] == "") {
				board[x][y] = "Empty";
			}
			else if (board[x][y] == "Empty") {

			}
			else {
				// The only possible other entry for board[x][y] is a number that dictates how many empty squares there are in a row so we can convert
				// the value in board[x][y] into an integer and use that value to calculate how many empty squares should be added.

				int numOfEmptySquares = std::stoi(board[x][y]);

				//This first loop determines how many times the next loop will be run. e.g. if we need 5 empty squares, the next loop will run 4 times.
				//It also swaps out the integer in the table 
				//Not going to lie I kind of forgot that While loops existed when coding this
				for (int k = 0; k < numOfEmptySquares - 1; k++) {
					board[x][y] = "Empty";
					for (int i = 7; i > x; i--) {
						board[i][y] = board[i - 1][y];
					}
				}

				if (numOfEmptySquares == 1) {
					board[x][y] = "Empty";
				}

			}

		}
	}


	player1sTurn = true;
}

string BoardSetup::ReturnPieceName(int xPosition, int yPosition) {
	return board[xPosition][yPosition];
}