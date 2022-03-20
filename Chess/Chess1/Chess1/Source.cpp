#include <iostream>
#include <string>

//Include all of the header files of our classes:
#include"BoardSetup.h"
#include"Pieces.h"
#include"PossibleMoves.h"

// The following 2 lines just allow me to just write "cout" and "endl" instead of "std::cout" and "std::endl". This is just to make it easier to read and write.
using std::cout;
using std::endl;
using std::string;

// This class defines a number for each piece so that they can be stored in an array. Black pieces will have values of the piece plus 7, therefore if a piece number is < 7 it is white.








int main() {
	
	int whileLoop = 1;
	BoardSetup DefaultBoard;
	int xPosition, yPosition, newXPosition, newYPosition;

	while (whileLoop == 1)
	{

		for (int y = 7; y > -1; y--)
		{
			for (int x = 0; x < 8; x++)
			{
				cout << DefaultBoard.board[x][y] << " ";
			}
			cout << endl;
		}

		cout << "Enter an x position." << endl;
		std::cin >> xPosition;
		xPosition = xPosition - 1;
		//Typing in 10 will end the program
		if (xPosition == 9) {
			break;
		}
		cout << "Enter a y position." << endl;
		std::cin >> yPosition;
		yPosition = yPosition - 1;

		
		string PieceName = DefaultBoard.board[xPosition][yPosition];

		if (PieceName == "Empty") {
			cout << "You have selected an empty square" << endl;
			continue;
		}

		Pieces TestPiece(PieceName);

		if (DefaultBoard.player1sTurn == true && TestPiece.colour == 'b') {
			cout << "It is white to play. You can't select a black piece." << endl;
			continue;
		}
		else if (DefaultBoard.player1sTurn == false && TestPiece.colour == 'w') {
			cout << "It is black to play. You can't select a white piece." << endl;
			continue;
		}

		PossibleMoves arrayOfPossibleMoves(DefaultBoard, TestPiece, xPosition, yPosition);

		for (int y = 7; y > -1; y--)
		{
			for (int x = 0; x < 8; x++)
			{
				cout << std::boolalpha << arrayOfPossibleMoves.validMoves[x][y] << " ";
			}
			cout << endl;
		}

		cout << "Enter a new x position." << endl;
		std::cin >> newXPosition;
		newXPosition = newXPosition - 1;
		cout << "Enter a new y position." << endl;
		std::cin >> newYPosition;
		newYPosition = newYPosition - 1;

		if (arrayOfPossibleMoves.validMoves[newXPosition][newYPosition] == true) {
			DefaultBoard.board[newXPosition][newYPosition] = DefaultBoard.board[xPosition][yPosition];
			DefaultBoard.board[xPosition][yPosition] = "Empty";
			if (DefaultBoard.player1sTurn == true) {
				DefaultBoard.player1sTurn = false;
			}
			else {
				DefaultBoard.player1sTurn = true;
			}
		}
		else
		{
			cout << "invalid move" << endl;
		}

		cout << endl;
	}
	cout << '\n' << "Ending Program" << '\n';
	
	
	
	// Values needed: int key, char colour, int xPosition, int yPosition, string board[8][8].
}