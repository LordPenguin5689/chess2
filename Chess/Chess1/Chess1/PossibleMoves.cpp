#include"BoardSetup.h" 
#include"Pieces.h"
#include"PossibleMoves.h"

#include <iostream>
#include <string>

//Default constructor that sets every value on the board as true so it is obvious something has gone wrong. Should never run.
PossibleMoves::PossibleMoves() {
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			validMoves[x][y] = true;
		}
	}
}

PossibleMoves::PossibleMoves(BoardSetup DefaultBoard, Pieces TestData, int xPosition, int yPosition) {

	string board[8][8] = {};
	int key = TestData.key;
	char colour = TestData.colour;
	string temp;


	Pieces pieceInTheWay("White Pawn");

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[x][y] = DefaultBoard.board[x][y];
		}
	}

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			validMoves[x][y] = false;
		}
	}


	//Start with white pawn
	if (key == 0 && colour == 'w') {
		//If pawn is on the right most side, the only potential possible diagonal move is right and up.
		//Also there is no need to check y position as a pawn cannot be on the 8th row or it will promote.
		if (xPosition == 0 && board[1][yPosition + 1] != "Empty") {
			pieceInTheWay.setValues(board[1][yPosition + 1]);
			if (pieceInTheWay.colour == 'w') {
				//If the piece in the way is white, we cannot take because our pawn is white.
				validMoves[1][yPosition + 1] = false;
			}
			else
			{
				//if it isn't white we can take it. First we should check if moving will put the king in check.
				
				temp = board[1][yPosition + 1];
				DefaultBoard.board[1][yPosition + 1] = "White Pawn";
				DefaultBoard.board[0][yPosition] = "Empty";

				//If the king would be in check by moving this piece, we don't make the move valid.
				if (kingIsAttacked(DefaultBoard, 'w') == true) {
					
				}
				else {
					validMoves[1][yPosition + 1] = true;
				}
				DefaultBoard.board[1][yPosition] = "White Pawn";
				DefaultBoard.board[0][yPosition + 1] = temp;
			}
		}
		//If pawn is on the right most side, the only potential possible diagonal move is left and up.
		else if (xPosition == 7 && board[6][yPosition + 1] != "Empty") {
			pieceInTheWay.setValues(board[6][yPosition + 1]);
			if (pieceInTheWay.colour == 'w') {
				//If the piece in the way is white, we cannot take because our pawn is white.
				validMoves[6][yPosition + 1] = false;
			}
			else
			{
				//if it isn't white we can take it.First we should check if moving will put the king in check.

				temp = board[6][yPosition + 1];
				DefaultBoard.board[6][yPosition + 1] = "White Pawn";
				DefaultBoard.board[7][yPosition] = "Empty";

				//If the king would be in check by moving this piece, we don't make the move valid.
				if (kingIsAttacked(DefaultBoard, 'w') == true) {
				
				}
				else {
					validMoves[6][yPosition + 1] = true;
				}
				DefaultBoard.board[7][yPosition] = "White Pawn";
				DefaultBoard.board[6][yPosition + 1] = temp;
			}
		}
		else if (xPosition != 0 && xPosition != 7)
		{
			if (board[xPosition - 1][yPosition + 1] != "Empty") {
				//Check diagonally left and up
				pieceInTheWay.setValues(board[xPosition - 1][yPosition + 1]);
				if (pieceInTheWay.colour == 'w') {
					//If the piece in the way is white, we cannot take because our pawn is white.
					validMoves[xPosition - 1][yPosition + 1] = false;
				}
				else
				{
					//if it isn't white we can take it. First we should check if moving will put the king in check.

					temp = board[xPosition - 1][yPosition + 1];
					DefaultBoard.board[xPosition - 1][yPosition + 1] = "White Pawn";
					DefaultBoard.board[xPosition][yPosition] = "Empty";

					//If the king would be in check by moving this piece, we don't make the move valid.
					if (kingIsAttacked(DefaultBoard, 'w') == true) {

					}
					else {
						validMoves[xPosition - 1][yPosition + 1] = true;
					}
					DefaultBoard.board[xPosition][yPosition] = "White Pawn";
					DefaultBoard.board[xPosition - 1][yPosition + 1] = temp;
				}
			}
			else if (board[xPosition + 1][yPosition + 1] != "Empty") {
				//Check diagonally right and up
				pieceInTheWay.setValues(board[xPosition + 1][yPosition + 1]);
				if (pieceInTheWay.colour == 'w') {
					//If the piece in the way is white, we cannot take because our pawn is white.
					validMoves[xPosition + 1][yPosition + 1] = false;
				}
				else
				{
					//if it isn't white we can take it. First we should check if moving will put the king in check.

					temp = board[xPosition + 1][yPosition + 1];
					DefaultBoard.board[xPosition + 1][yPosition + 1] = "White Pawn";
					DefaultBoard.board[xPosition][yPosition] = "Empty";

					//If the king would be in check by moving this piece, we don't make the move valid.
					if (kingIsAttacked(DefaultBoard, 'w') == true) {

					}
					else {
						validMoves[xPosition + 1][yPosition + 1] = true;
					}
					DefaultBoard.board[xPosition][yPosition] = "White Pawn";
					DefaultBoard.board[xPosition + 1][yPosition + 1] = temp;
				}
			}
		}

		//Next check straight ahead.
		//If directly infront of the piece is empty, we can move there.
		if (board[xPosition][yPosition + 1] == "Empty") {
			//Check if moving the piece will put the king in check first.
			DefaultBoard.board[xPosition ][yPosition + 1] = "White Pawn";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check by moving this piece, we don't make the move valid.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {

			}
			else {
				validMoves[xPosition][yPosition + 1] = true;
			}
			DefaultBoard.board[xPosition][yPosition] = "White Pawn";
			DefaultBoard.board[xPosition][yPosition + 1] = "Empty";

			//If the pawn is on the second rank (yPosition 1), the pawn hasn't moved so it may move an additional sqaure
			//(as long as the piece was allowed to move one square ahead)
			if (yPosition == 1 && board[xPosition][yPosition + 2] == "Empty" && validMoves[xPosition][yPosition + 1] == true) {

				validMoves[xPosition][yPosition + 2] = true;
			}
		}

	}
	//Next is Black pawn so it is just the same but y position goes down
	else if (key == 0 && colour == 'b') {
		//If pawn is on the right most side, the only potential possible diagonal move is right and down.
		//Also there is no need to check y position as a pawn cannot be on the 1st row or it will promote.
		if (xPosition == 0 && board[1][yPosition - 1] != "Empty") {
			pieceInTheWay.setValues(board[1][yPosition - 1]);
			if (pieceInTheWay.colour == 'b') {
				//If the piece in the way is black, we cannot take because our pawn is black.
				validMoves[1][yPosition - 1] = false;
			}
			else
			{
				//if it isn't black we can take it. First we should check if moving will put the king in check.

				temp = board[1][yPosition - 1];
				DefaultBoard.board[1][yPosition - 1] = "Black Pawn";
				DefaultBoard.board[0][yPosition] = "Empty";

				//If the king would be in check by moving this piece, we don't make the move valid.
				if (kingIsAttacked(DefaultBoard, 'b') == true) {

				}
				else {
					validMoves[1][yPosition - 1] = true;
				}
				DefaultBoard.board[1][yPosition] = "Black Pawn";
				DefaultBoard.board[0][yPosition - 1] = temp;
			}
		}
		//If pawn is on the right most side, the only potential possible diagonal move is left and down.
		else if (xPosition == 7 && board[1][yPosition - 1] != "Empty") {
			pieceInTheWay.setValues(board[6][yPosition - 1]);
			if (pieceInTheWay.colour == 'b') {
				//If the piece in the way is black, we cannot take because our pawn is black.
				validMoves[xPosition - 1][yPosition - 1] = false;
			}
			else
			{
				//if it isn't black we can take it.First we should check if moving will put the king in check.

				temp = board[6][yPosition - 1];
				DefaultBoard.board[6][yPosition - 1] = "Black Pawn";
				DefaultBoard.board[7][yPosition] = "Empty";

				//If the king would be in check by moving this piece, we don't make the move valid.
				if (kingIsAttacked(DefaultBoard, 'b') == true) {

				}
				else {
					validMoves[6][yPosition - 1] = true;
				}
				DefaultBoard.board[7][yPosition] = "Black Pawn";
				DefaultBoard.board[6][yPosition - 1] = temp;
			}
		}
		else if (xPosition != 0 && xPosition != 7)
		{
			if (board[xPosition - 1][yPosition - 1] != "Empty") {
				//Check diagonally left and down
				pieceInTheWay.setValues(board[xPosition - 1][yPosition - 1]);
				if (pieceInTheWay.colour == 'b') {
					//If the piece in the way is black, we cannot take because our pawn is black.
					validMoves[6][yPosition - 1] = false;
				}
				else
				{
					//if it isn't black we can take it. First we should check if moving will put the king in check.

					temp = board[xPosition - 1][yPosition - 1];
					DefaultBoard.board[xPosition - 1][yPosition - 1] = "Black Pawn";
					DefaultBoard.board[xPosition][yPosition] = "Empty";

					//If the king would be in check by moving this piece, we don't make the move valid.
					if (kingIsAttacked(DefaultBoard, 'b') == true) {

					}
					else {
						validMoves[xPosition - 1][yPosition - 1] = true;
					}
					DefaultBoard.board[xPosition][yPosition] = "Black Pawn";
					DefaultBoard.board[xPosition - 1][yPosition - 1] = temp;
				}
			}
			else if (board[xPosition + 1][yPosition - 1] != "Empty") {
				//Check diagonally right and down
				pieceInTheWay.setValues(board[xPosition + 1][yPosition - 1]);
				if (pieceInTheWay.colour == 'b') {
					//If the piece in the way is black, we cannot take because our pawn is black.
					validMoves[6][yPosition - 1] = false;
				}
				else
				{
					//if it isn't black we can take it. First we should check if moving will put the king in check.

					temp = board[xPosition + 1][yPosition - 1];
					DefaultBoard.board[xPosition + 1][yPosition - 1] = "Black Pawn";
					DefaultBoard.board[xPosition][yPosition] = "Empty";

					//If the king would be in check by moving this piece, we don't make the move valid.
					if (kingIsAttacked(DefaultBoard, 'b') == true) {

					}
					else {
						validMoves[xPosition + 1][yPosition - 1] = true;
					}
					DefaultBoard.board[xPosition][yPosition] = "Black Pawn";
					DefaultBoard.board[xPosition + 1][yPosition - 1] = temp;
				}
			}
		}

		//Next check straight ahead.
		//If directly infront of the piece is empty, we can move there.
		if (board[xPosition][yPosition - 1] == "Empty") {
			//Check if moving the piece will put the king in check first.
			DefaultBoard.board[xPosition][yPosition - 1] = "Black Pawn";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check by moving this piece, we don't make the move valid.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
			}
			else {
				validMoves[xPosition][yPosition - 1] = true;
			}
			DefaultBoard.board[xPosition][yPosition] = "Black Pawn";
			DefaultBoard.board[xPosition][yPosition - 1] = "Empty";

			//If the pawn is on the second rank (yPosition 1), the pawn hasn't moved so it may move an additional sqaure
			//(as long as the piece was allowed to move one square ahead)
			if (yPosition == 6 && board[xPosition][yPosition - 2] == "Empty" && validMoves[xPosition][yPosition - 1] == true) {

				validMoves[xPosition][yPosition - 2] = true;
			}
		}
	}

	//Next lets program the white bishop because I am not in the mood to do the knight just yet.
	else if (key == 2 && colour == 'w') {

		//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
		int i = 1;
		bool pathIsClear = true;

		while (xPosition - i >= 0 && yPosition + i <= 7 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition + i];
			DefaultBoard.board[xPosition - i][yPosition + i] = "White Bishop";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Bishop";
			DefaultBoard.board[xPosition - i][yPosition + i] = temp;

			if (board[xPosition - i][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition + i]);
				if (pieceInTheWay.key == 'b')
				{
					//If the piece in the way is black, allow it to be taken. 
					//The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition - i][yPosition + i] = true;
					
				}
				else
				{
					//If the piece is white, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition - i][yPosition + i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition - i][yPosition + i] = true;
			}
			i++;
		}

		//Next direction is diagonally up and right. Also we need to reset i and pathIsClear variables after every while loop.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && yPosition + i <= 7 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition + i];
			DefaultBoard.board[xPosition + i][yPosition + i] = "White Bishop";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}
			DefaultBoard.board[xPosition][yPosition] = "White Bishop";
			DefaultBoard.board[xPosition + i][yPosition + i] = temp;

			if (board[xPosition + i][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition + i]);
				if (pieceInTheWay.colour == 'b'){
					//If the piece in the way is black, allow it to be taken. 
					//The loop will then break, meaning all squares on the other side of the piece will not be valid.
						validMoves[xPosition + i][yPosition + i] = true;
				}
				else
				{
					//If the piece is white, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition + i][yPosition + i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition + i][yPosition + i] = true;
			}
			i++;
		}

		//Next direction is diagonally down and right. Again resetting i and pathIsClear variables.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && yPosition - i >= 0 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition - i];
			DefaultBoard.board[xPosition + i][yPosition - i] = "White Bishop";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}
			DefaultBoard.board[xPosition][yPosition] = "White Bishop";
			DefaultBoard.board[xPosition + i][yPosition - i] = temp;

			if (board[xPosition + i][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition - i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, allow it to be taken. 
					//The loop will then break, meaning all squares on the other side of the piece will not be valid.					
					validMoves[xPosition + i][yPosition - i] = true;
				}
				else
				{
					//If the piece is white, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition + i][yPosition - i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition + i][yPosition - i] = true;
			}
			i++;
		}

		//And the final direction is diagonally down and left.
		i = 1;
		pathIsClear = true;
		while (xPosition - i >= 0 && yPosition - i >= 0 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition - i];
			DefaultBoard.board[xPosition - i][yPosition - i] = "White Bishop";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}
			DefaultBoard.board[xPosition][yPosition] = "White Bishop";
			DefaultBoard.board[xPosition - i][yPosition - i] = temp;

			if (board[xPosition - i][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition - i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, allow it to be taken. 
					//The loop will then break, meaning all squares on the other side of the piece will not be valid.					
					validMoves[xPosition - i][yPosition - i] = true;
				}
				else
				{
					//If the piece is white, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition - i][yPosition - i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition - i][yPosition - i] = true;
			}
			i++;
		}

		//The previous code does not account for checks, but I will write a function with line of sight of for the King which will run before move is validated.
	}
	//Same as the previous while loops for white bishops but for black ones.
	else if (key == 2 && colour == 'b')
	{

		//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
		int i = 1;
		bool pathIsClear = true;

		while (xPosition - i >= 0 && yPosition + i <= 7 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition + i];
			DefaultBoard.board[xPosition - i][yPosition + i] = "Black Bishop";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Bishop";
			DefaultBoard.board[xPosition - i][yPosition + i] = temp;

			if (board[xPosition - i][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition + i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition - i][yPosition + i] = true;
				}
				else
				{
					//If the piece is black, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition - i][yPosition + i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition - i][yPosition + i] = true;
			}
			i++;
		}

		//Next direction is diagonally up and right. Also we need to reset i and pathIsClear variables after every while loop.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && yPosition + i <= 7 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition + i];
			DefaultBoard.board[xPosition + i][yPosition + i] = "Black Bishop";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Bishop";
			DefaultBoard.board[xPosition + i][yPosition + i] = temp;

			if (board[xPosition + i][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition + i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition + i][yPosition + i] = true;
				}
				else
				{
					//If the piece is black, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition + i][yPosition + i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition + i][yPosition + i] = true;
			}
			i++;
		}

		//Next direction is diagonally down and right. Again resetting i and pathIsClear variables.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && yPosition - i >= 0 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition - i];
			DefaultBoard.board[xPosition + i][yPosition - i] = "Black Bishop";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Bishop";
			DefaultBoard.board[xPosition + i][yPosition - i] = temp;

			if (board[xPosition + i][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition - i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition + i][yPosition - i] = true;
				}
				else
				{
					//If the piece is black, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition + i][yPosition - i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition + i][yPosition - i] = true;
			}
			i++;
		}

		//And the final direction is diagonally down and left.
		i = 1;
		pathIsClear = true;
		while (xPosition - i >= 0 && yPosition - i >= 0 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition - i];
			DefaultBoard.board[xPosition - i][yPosition - i] = "Black Bishop";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Bishop";
			DefaultBoard.board[xPosition - i][yPosition - i] = temp;

			if (board[xPosition - i][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition - i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition - i][yPosition - i] = true;
				}
				else
				{
					//If the piece is black, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition - i][yPosition - i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition - i][yPosition - i] = true;
			}
			i++;
		}

		//The previous code does not account for checks, but I will write a function with line of sight of for the King which will run before move is validated.
	}

	//The next piece to do is the rook, starting with white. Still don't want to do knight even though it is just 8 if statements.
	else if (key == 3 && colour == 'w')
	{

		//lets do straight up first
		int i = 1;
		bool pathIsClear = true;
		while (yPosition + i <= 7 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition][yPosition + i];
			DefaultBoard.board[xPosition][yPosition + i] = "White Rook";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Rook";
			DefaultBoard.board[xPosition][yPosition + i] = temp;

			if (board[xPosition][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition][yPosition + i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition][yPosition + i] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is black, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition][yPosition + i] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition][yPosition + i] = true;
			}
			i++;
		}

		//Same but for straight right.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition];
			DefaultBoard.board[xPosition + i][yPosition] = "White Rook";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Rook";
			DefaultBoard.board[xPosition + i][yPosition] = temp;

			if (board[xPosition + i][yPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition + i][yPosition] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is black, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition + i][yPosition] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition + i][yPosition] = true;
			}
			i++;
		}

		//Same again but for straight down
		i = 1;
		pathIsClear = true;
		while (yPosition - i >= 0 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition][yPosition - i];
			DefaultBoard.board[xPosition][yPosition - i] = "White Rook";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Rook";
			DefaultBoard.board[xPosition][yPosition - i] = temp;

			if (board[xPosition][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition][yPosition - i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition][yPosition - i] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is black, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition][yPosition - i] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition][yPosition - i] = true;
			}
			i++;
		}

		//Same but for straight left.
		i = 1;
		pathIsClear = true;
		while (xPosition - i >= 0 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition];
			DefaultBoard.board[xPosition - i][yPosition] = "White Rook";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Rook";
			DefaultBoard.board[xPosition - i][yPosition] = temp;

			if (board[xPosition - i][yPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition - i][yPosition] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is black, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition - i][yPosition] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition - i][yPosition] = true;
			}
			i++;
		}

		//Again checks are not yet implemented but I will write a function to check a move for checks and then implement it here.
	}

	//Now doing the black rook.
	else if (key == 3 && colour == 'b')
	{

		//lets do straight up first
		int i = 1;
		bool pathIsClear = true;
		while (yPosition + i <= 7 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition][yPosition + i];
			DefaultBoard.board[xPosition][yPosition + i] = "Black Rook";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Rook";
			DefaultBoard.board[xPosition][yPosition + i] = temp;

			if (board[xPosition][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition][yPosition + i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition][yPosition + i] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is white, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition][yPosition + i] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition][yPosition + i] = true;
			}
			i++;
		}

		//Same but for straight right.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition];
			DefaultBoard.board[xPosition + i][yPosition] = "Black Rook";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Rook";
			DefaultBoard.board[xPosition + i][yPosition] = temp;

			if (board[xPosition + i][yPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition + i][yPosition] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is white, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition + i][yPosition] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition + i][yPosition] = true;
			}
			i++;
		}

		//Same again but for straight down
		i = 1;
		pathIsClear = true;
		while (yPosition - i >= 0 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition][yPosition - i];
			DefaultBoard.board[xPosition][yPosition - i] = "Black Rook";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Rook";
			DefaultBoard.board[xPosition][yPosition - i] = temp;

			if (board[xPosition][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition][yPosition - i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition][yPosition - i] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is white, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition][yPosition - i] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition][yPosition - i] = true;
			}
			i++;
		}

		//Same but for straight left.
		i = 1;
		pathIsClear = true;
		while (xPosition - i >= 0 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition];
			DefaultBoard.board[xPosition - i][yPosition] = "Black Rook";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Rook";
			DefaultBoard.board[xPosition - i][yPosition] = temp;

			if (board[xPosition - i][yPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition - i][yPosition] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is white, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition - i][yPosition] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition - i][yPosition] = true;
			}
			i++;
		}

		//Again checks are not yet implemented but I will write a function to check a move for checks and then implement it here.
	}

	//Time to finally pluck up the courage and do the maths to implement knight moves, starting with the white knight.

	bool weCanSkip = false;
	if (key == 1 && colour == 'w')
	{
		//We can simply remove the knight from the board, and then check if the king would be in check.
		//This is because knight moves always change the diagonal and line it is on, so we know if it moves, it will open a line.
		DefaultBoard.board[xPosition][yPosition] = "Empty";
		if (kingIsAttacked(DefaultBoard, 'w') == true) {
			weCanSkip = true;
		}
		DefaultBoard.board[xPosition][yPosition] = "White Knight";

		if (weCanSkip == false) {
			//I am going to implement this almost manually. If this makes you cringe that is okay. I don't have the brain power right now to implement a more efficient system.
		//I may come back to this to increase the efficiency.
		//First lets go 2 left and 1 up
			if (xPosition - 2 >= 0 && yPosition + 1 <= 7)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition - 2][yPosition + 1] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition - 2][yPosition + 1]);
					//Now check if piece is white.
					if (pieceInTheWay.colour == 'w')
					{
						//If the piece is white, because our knight is white, we can't move to that place.
						validMoves[xPosition - 2][yPosition + 1] = false;
					}
					else
					{
						//If the piece is black, because our knight is white, we can just take it.
						validMoves[xPosition - 2][yPosition + 1] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition - 2][yPosition + 1] = true;
				}

			//Now to repeat for 1 left, 2 up.
			if (xPosition - 1 >= 0 && yPosition + 2 <= 7)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition - 1][yPosition + 2] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition - 1][yPosition + 2]);
					//Now check if piece is white.
					if (pieceInTheWay.colour == 'w')
					{
						//If the piece is white, because our knight is white, we can't move to that place.
						validMoves[xPosition - 1][yPosition + 2] = false;
					}
					else
					{
						//If the piece is black, because our knight is white, we can just take it.
						validMoves[xPosition - 1][yPosition + 2] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition - 1][yPosition + 2] = true;
				}

			//Now to repeat for 1 right, 2 up.
			if (xPosition + 1 <= 7 && yPosition + 2 <= 7)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition + 1][yPosition + 2] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition + 1][yPosition + 2]);
					//Now check if piece is white.
					if (pieceInTheWay.colour == 'w')
					{
						//If the piece is white, because our knight is white, we can't move to that place.
						validMoves[xPosition + 1][yPosition + 2] = false;
					}
					else
					{
						//If the piece is black, because our knight is white, we can just take it.
						validMoves[xPosition + 1][yPosition + 2] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition + 1][yPosition + 2] = true;
				}

			//Repeat for 2 right, 1 up.
			if (xPosition + 2 <= 7 && yPosition + 1 <= 7)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition + 2][yPosition + 1] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition + 2][yPosition + 1]);
					//Now check if piece is white.
					cout << pieceInTheWay.colour << endl;
					if (pieceInTheWay.colour == 'w')
					{
						//If the piece is white, because our knight is white, we can't move to that place.
						validMoves[xPosition + 2][yPosition + 1] = false;
					}
					else
					{
						//If the piece is black, because our knight is white, we can just take it.
						validMoves[xPosition + 2][yPosition + 1] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition + 2][yPosition + 1] = true;
				}

			//Repeat for 2 right, 1 down.
			if (xPosition + 2 <= 7 && yPosition - 1 >= 0)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition + 2][yPosition - 1] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition + 2][yPosition - 1]);
					//Now check if piece is white.
					if (pieceInTheWay.colour == 'w')
					{
						//If the piece is white, because our knight is white, we can't move to that place.
						validMoves[xPosition + 2][yPosition - 1] = false;
					}
					else
					{
						//If the piece is black, because our knight is white, we can just take it.
						validMoves[xPosition + 2][yPosition - 1] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition + 2][yPosition - 1] = true;
				}

			//Repeat for 1 right, 2 down
			if (xPosition + 1 <= 7 && yPosition - 2 >= 0)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition + 1][yPosition - 2] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition + 1][yPosition - 2]);
					//Now check if piece is white.
					if (pieceInTheWay.colour == 'w')
					{
						//If the piece is white, because our knight is white, we can't move to that place.
						validMoves[xPosition + 1][yPosition - 2] = false;
					}
					else
					{
						//If the piece is black, because our knight is white, we can just take it.
						validMoves[xPosition + 1][yPosition - 2] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition + 1][yPosition - 2] = true;
				}

			//Repeat for 1 left, 2 down
			if (xPosition - 1 >= 0 && yPosition - 2 >= 0)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition - 1][yPosition - 2] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition - 1][yPosition - 2]);
					//Now check if piece is white.
					if (pieceInTheWay.colour == 'w')
					{
						//If the piece is white, because our knight is white, we can't move to that place.
						validMoves[xPosition - 1][yPosition - 2] = false;
					}
					else
					{
						//If the piece is black, because our knight is white, we can just take it.
						validMoves[xPosition - 1][yPosition - 2] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition - 1][yPosition - 2] = true;
				}

			//Repeat for 2 left, 1 down
			if (xPosition - 2 >= 0 && yPosition - 1 >= 0)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition - 2][yPosition - 1] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition - 1][yPosition - 2]);
					//Now check if piece is white.
					if (pieceInTheWay.colour == 'w')
					{
						//If the piece is white, because our knight is white, we can't move to that place.
						validMoves[xPosition - 2][yPosition - 1] = false;
					}
					else
					{
						//If the piece is black, because our knight is white, we can just take it.
						validMoves[xPosition - 2][yPosition - 1] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition - 2][yPosition - 1] = true;
				}
		}
		
	}

	//Probably don't need the next line but doing it just in case.
	weCanSkip = false;
	//Next is Black Knight
	if (key == 1 && colour == 'b')
	{
		//We can simply remove the knight from the board, and then check if the king would be in check.
		//This is because knight moves always change the diagonal and line it is on, so we know if it moves, it will open a line.
		DefaultBoard.board[xPosition][yPosition] = "Empty";
		if (kingIsAttacked(DefaultBoard, 'w') == true) {
			weCanSkip = true;
		}
		DefaultBoard.board[xPosition][yPosition] = "White Knight";

		if (weCanSkip == false) {
			//I am going to implement this almost manually. If this makes you cringe that is okay. I don't have the brain power right now to implement a more efficient system.
		//I may come back to this to increase the efficiency.
		//First lets go 2 left and 1 up
			if (xPosition - 2 >= 0 && yPosition + 1 <= 7)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition - 2][yPosition + 1] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition - 2][yPosition + 1]);
					//Now check if piece is black.
					if (pieceInTheWay.colour == 'b')
					{
						//If the piece is black, because our knight is black, we can't move to that place.
						validMoves[xPosition - 2][yPosition + 1] = false;
					}
					else
					{
						//If the piece is white, because our knight is black, we can just take it.
						validMoves[xPosition - 2][yPosition + 1] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition - 2][yPosition + 1] = true;
				}

			//Now to repeat for 1 left, 2 up.
			if (xPosition - 1 >= 0 && yPosition + 2 <= 7)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition - 1][yPosition + 2] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition - 1][yPosition + 2]);
					//Now check if piece is black.
					if (pieceInTheWay.colour == 'b')
					{
						//If the piece is black, because our knight is black, we can't move to that place.
						validMoves[xPosition - 1][yPosition + 2] = false;
					}
					else
					{
						//If the piece is white, because our knight is black, we can just take it.
						validMoves[xPosition - 1][yPosition + 2] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition - 1][yPosition + 2] = true;
				}

			//Now to repeat for 1 right, 2 up.
			if (xPosition + 1 <= 7 && yPosition + 2 <= 7)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition + 1][yPosition + 2] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition + 1][yPosition + 2]);
					//Now check if piece is black.
					if (pieceInTheWay.colour == 'b')
					{
						//If the piece is black, because our knight is black, we can't move to that place.
						validMoves[xPosition + 1][yPosition + 2] = false;
					}
					else
					{
						//If the piece is white, because our knight is black, we can just take it.
						validMoves[xPosition + 1][yPosition + 2] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition + 1][yPosition + 2] = true;
				}

			//Repeat for 2 right, 1 up.
			if (xPosition + 2 <= 7 && yPosition + 1 <= 7)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition + 2][yPosition + 1] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition + 2][yPosition + 1]);
					//Now check if piece is black.
					if (pieceInTheWay.colour == 'b')
					{
						//If the piece is black, because our knight is black, we can't move to that place.
						validMoves[xPosition + 2][yPosition + 1] = false;
					}
					else
					{
						//If the piece is white, because our knight is black, we can just take it.
						validMoves[xPosition + 2][yPosition + 1] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition + 2][yPosition + 1] = true;
				}

			//Repeat for 2 right, 1 down.
			if (xPosition + 2 <= 7 && yPosition - 1 >= 0)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition + 2][yPosition - 1] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition + 2][yPosition - 1]);
					//Now check if piece is black.
					if (pieceInTheWay.colour == 'b')
					{
						//If the piece is black, because our knight is black, we can't move to that place.
						validMoves[xPosition + 2][yPosition - 1] = false;
					}
					else
					{
						//If the piece is white, because our knight is black, we can just take it.
						validMoves[xPosition + 2][yPosition - 1] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition + 2][yPosition - 1] = true;
				}

			//Repeat for 1 right, 2 down
			if (xPosition + 1 <= 7 && yPosition - 2 >= 0)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition + 1][yPosition - 2] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition + 1][yPosition - 2]);
					//Now check if piece is black.
					if (pieceInTheWay.colour == 'b')
					{
						//If the piece is black, because our knight is black, we can't move to that place.
						validMoves[xPosition + 1][yPosition - 2] = false;
					}
					else
					{
						//If the piece is white, because our knight is black, we can just take it.
						validMoves[xPosition + 1][yPosition - 2] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition + 1][yPosition - 2] = true;
				}

			//Repeat for 1 left, 2 down
			if (xPosition - 1 >= 0 && yPosition - 2 >= 0)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition - 1][yPosition - 2] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition - 1][yPosition - 2]);
					//Now check if piece is black.
					if (pieceInTheWay.colour == 'b')
					{
						//If the piece is black, because our knight is black, we can't move to that place.
						validMoves[xPosition - 1][yPosition - 2] = false;
					}
					else
					{
						//If the piece is white, because our knight is black, we can just take it.
						validMoves[xPosition - 1][yPosition - 2] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition - 1][yPosition - 2] = true;
				}

			//Repeat for 2 left, 1 down
			if (xPosition - 2 >= 0 && yPosition - 1 >= 0)
				//Now to check if a piece is in the position we want to jump to.
				if (board[xPosition - 2][yPosition - 1] != "Empty")
				{
					pieceInTheWay.setValues(board[xPosition - 1][yPosition - 2]);
					//Now check if piece is black.
					if (pieceInTheWay.colour == 'b')
					{
						//If the piece is black, because our knight is black, we can't move to that place.
						validMoves[xPosition - 2][yPosition - 1] = false;
					}
					else
					{
						//If the piece is white, because our knight is black, we can just take it.
						validMoves[xPosition - 2][yPosition - 1] = true;
					}
				}
				else
				{
					//If there is no piece in the square, we can just declare the square valid.
					validMoves[xPosition - 2][yPosition - 1] = true;
				}
		}

		
	}

	//Next is to do the Queen. There is nothing new or interesting here, it is just a combination of the bishop and rook move validation.
	else if (key == 4 && colour == 'w') {
		//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
		int i = 1;
		bool pathIsClear = true;

		while (xPosition - i >= 0 && yPosition + i <= 7 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition + i];
			DefaultBoard.board[xPosition - i][yPosition + i] = "White Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Queen";
			DefaultBoard.board[xPosition - i][yPosition + i] = temp;

			if (board[xPosition - i][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition + i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition - i][yPosition + i] = true;
				}
				else
				{
					//If the piece is white, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition - i][yPosition + i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition - i][yPosition + i] = true;
			}
			i++;
		}

		//Next direction is diagonally up and right. Also we need to reset i and pathIsClear variables after every while loop.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && yPosition + i <= 7 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition + i];
			DefaultBoard.board[xPosition + i][yPosition + i] = "White Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}
			DefaultBoard.board[xPosition][yPosition] = "White Queen";
			DefaultBoard.board[xPosition + i][yPosition + i] = temp;

			if (board[xPosition + i][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition + i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition + i][yPosition + i] = true;
				}
				else
				{
					//If the piece is white, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition + i][yPosition + i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition + i][yPosition + i] = true;
			}
			i++;
		}

		//Next direction is diagonally down and right. Again resetting i and pathIsClear variables.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && yPosition - i >= 0 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition - i];
			DefaultBoard.board[xPosition + i][yPosition - i] = "White Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}
			DefaultBoard.board[xPosition][yPosition] = "White Queen";
			DefaultBoard.board[xPosition + i][yPosition - i] = temp;

			if (board[xPosition + i][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition - i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition + i][yPosition - i] = true;
				}
				else
				{
					//If the piece is white, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition + i][yPosition - i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition + i][yPosition - i] = true;
			}
			i++;
		}

		//And the final diagonal direction is diagonally down and left.
		i = 1;
		pathIsClear = true;
		while (xPosition - i >= 0 && yPosition - i >= 0 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition - i];
			DefaultBoard.board[xPosition - i][yPosition - i] = "White Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}
			DefaultBoard.board[xPosition][yPosition] = "White Queen";
			DefaultBoard.board[xPosition - i][yPosition - i] = temp;

			if (board[xPosition - i][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition - i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition - i][yPosition - i] = true;
				}
				else
				{
					//If the piece is white, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition - i][yPosition - i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition - i][yPosition - i] = true;
			}
			i++;
		}

		//lets do straight up first
		i = 1;
		pathIsClear = true;
		while (yPosition + i <= 7 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition][yPosition + i];
			DefaultBoard.board[xPosition][yPosition + i] = "White Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Queen";
			DefaultBoard.board[xPosition][yPosition + i] = temp;

			if (board[xPosition][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition][yPosition + i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition][yPosition + i] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is black, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition][yPosition + i] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition][yPosition + i] = true;
			}
			i++;
		}

		//Same but for straight right.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition];
			DefaultBoard.board[xPosition + i][yPosition] = "White Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Queen";
			DefaultBoard.board[xPosition + i][yPosition] = temp;

			if (board[xPosition + i][yPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition + i][yPosition] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is black, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition + i][yPosition] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition + i][yPosition] = true;
			}
			i++;
		}

		//Same again but for straight down
		i = 1;
		pathIsClear = true;
		while (yPosition - i >= 0 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition][yPosition - i];
			DefaultBoard.board[xPosition][yPosition - i] = "White Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Queen";
			DefaultBoard.board[xPosition][yPosition - i] = temp;

			if (board[xPosition][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition][yPosition - i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition][yPosition - i] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is black, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition][yPosition - i] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition][yPosition - i] = true;
			}
			i++;
		}

		//Same but for straight left.
		i = 1;
		pathIsClear = true;
		while (xPosition - i >= 0 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition];
			DefaultBoard.board[xPosition - i][yPosition] = "White Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'w') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "White Queen";
			DefaultBoard.board[xPosition - i][yPosition] = temp;

			if (board[xPosition - i][yPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition - i][yPosition] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is black, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition - i][yPosition] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition - i][yPosition] = true;
			}
			i++;
		}

		//Again checks are not yet implemented but I will write a function to check a move for checks and then implement it here.
	}

	// Now same but for black Queen.
	else if (key == 4 && colour == 'b') {

		//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
		int i = 1;
		bool pathIsClear = true;

		while (xPosition - i >= 0 && yPosition + i <= 7 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition + i];
			DefaultBoard.board[xPosition - i][yPosition + i] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition - i][yPosition + i] = temp;

			if (board[xPosition - i][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition + i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition - i][yPosition + i] = true;
				}
				else
				{
					//If the piece is black, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition - i][yPosition + i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition - i][yPosition + i] = true;
			}
			i++;
		}

		//Next direction is diagonally up and right. Also we need to reset i and pathIsClear variables after every while loop.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && yPosition + i <= 7 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition + i];
			DefaultBoard.board[xPosition + i][yPosition + i] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition + i][yPosition + i] = temp;

			if (board[xPosition + i][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition + i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition + i][yPosition + i] = true;
				}
				else
				{
					//If the piece is black, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition + i][yPosition + i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition + i][yPosition + i] = true;
			}
			i++;
		}

		//Next direction is diagonally down and right. Again resetting i and pathIsClear variables.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && yPosition - i >= 0 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition - i];
			DefaultBoard.board[xPosition + i][yPosition - i] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition + i][yPosition - i] = temp;

			if (board[xPosition + i][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition - i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition + i][yPosition - i] = true;
				}
				else
				{
					//If the piece is black, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition + i][yPosition - i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition + i][yPosition - i] = true;
			}
			i++;
		}

		//And the final diagonal direction is diagonally down and left.
		i = 1;
		pathIsClear = true;
		while (xPosition - i >= 0 && yPosition - i >= 0 && pathIsClear == true) {
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition - i];
			DefaultBoard.board[xPosition - i][yPosition - i] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition - i][yPosition - i] = temp;

			if (board[xPosition - i][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition - i]);
				if (pieceInTheWay.colour == 'w')
				{
					//If the piece in the way is white, allow it to be taken. The loop will then break, meaning all squares on the other side of the piece will not be valid.
					validMoves[xPosition - i][yPosition - i] = true;
				}
				else
				{
					//If the piece is black, it cannot be taken therefore there is no more valid moves in this direction.
					validMoves[xPosition - i][yPosition - i] = false;
				}
				pathIsClear = false;
			}
			else
			{
				validMoves[xPosition - i][yPosition - i] = true;
			}
			i++;
		}

		//The previous code does not account for checks, but I will write a function with line of sight of for the King which will run before move is validated.

		//lets do straight up first
		i = 1;
		pathIsClear = true;
		while (yPosition + i <= 7 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition][yPosition + i];
			DefaultBoard.board[xPosition][yPosition + i] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition + i] = temp;

			if (board[xPosition][yPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition][yPosition + i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition][yPosition + i] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is white, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition][yPosition + i] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition][yPosition + i] = true;
			}
			i++;
		}

		//Same but for straight right.
		i = 1;
		pathIsClear = true;
		while (xPosition + i <= 7 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition + i][yPosition];
			DefaultBoard.board[xPosition + i][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition + i][yPosition] = temp;

			if (board[xPosition + i][yPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition + i][yPosition]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition + i][yPosition] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is white, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition + i][yPosition] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition + i][yPosition] = true;
			}
			i++;
		}

		//Same again but for straight down
		i = 1;
		pathIsClear = true;
		while (yPosition - i >= 0 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition][yPosition - i];
			DefaultBoard.board[xPosition][yPosition - i] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition - i] = temp;

			if (board[xPosition][yPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition][yPosition - i]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition][yPosition - i] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is white, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition][yPosition - i] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition][yPosition - i] = true;
			}
			i++;
		}

		//Same but for straight left.
		i = 1;
		pathIsClear = true;
		while (xPosition - i >= 0 && pathIsClear)
		{
			//Lets check if moving the piece would cause the king to be in check first.
			temp = DefaultBoard.board[xPosition - i][yPosition];
			DefaultBoard.board[xPosition - i][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition][yPosition] = "Empty";

			//If the king would be in check, we can't move this piece.
			if (kingIsAttacked(DefaultBoard, 'b') == true) {
				pathIsClear = false;
				break;
			}

			DefaultBoard.board[xPosition][yPosition] = "Black Queen";
			DefaultBoard.board[xPosition - i][yPosition] = temp;

			if (board[xPosition - i][yPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[xPosition - i][yPosition]);
				if (pieceInTheWay.colour == 'b')
				{
					//If the piece in the way is black, that square is not a valid move and there are no more valid squares in that direction.
					validMoves[xPosition - i][yPosition] = false;
					pathIsClear = false;
				}
				else
				{
					//If the piece in the way is white, the piece can be taken but there are no more valid squares in that direction.
					validMoves[xPosition - i][yPosition] = true;
					pathIsClear = false;
				}
			}
			else
			{
				validMoves[xPosition - i][yPosition] = true;
			}
			i++;
		}

		//Again checks are not yet implemented but I will write a function to check a move for checks and then implement it here.
	}

	//Thank God this is over let me leave. 1000 lines of code later and I have finished the valid squares boolean 2d array except I haven't even done checks yet fml.
	//Can't wait to realise there is a mistake that I copy and pasted 20 times and will have to correct 20 times. If it is a logic error I might shoot myself.


	//Need to do the king.
	else if (key == 5 && colour == 'w')
	{

		//Checking one right to the king so it can't be on the far right side.
		if (xPosition != 7) {

			pieceInTheWay.setValues(board[xPosition + 1][yPosition]);
			if (pieceInTheWay.colour == 'b' || pieceInTheWay.key == 6) {
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition + 1;
				temp = board[xPosition + 1][yPosition];
				DefaultBoard.board[xPosition + 1][yPosition] = DefaultBoard.board[xPosition][yPosition];
				DefaultBoard.board[xPosition][yPosition] = "Empty";
				if (kingIsAttacked(DefaultBoard, 'w') == false) {
					validMoves[xPosition + 1][yPosition] = true;
				}
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition - 1;
				DefaultBoard.board[xPosition][yPosition] = "White King";
				DefaultBoard.board[xPosition + 1][yPosition] = temp;
			}

		}
		//Checking one below to the king so it can't be on the bottom row.
		if (yPosition != 0) {

			pieceInTheWay.setValues(board[xPosition][yPosition - 1]);
			if (pieceInTheWay.colour == 'b' || pieceInTheWay.key == 6) {
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition - 1;
				temp = board[xPosition][yPosition - 1];
				DefaultBoard.board[xPosition][yPosition - 1] = DefaultBoard.board[xPosition][yPosition];
				DefaultBoard.board[xPosition][yPosition] = "Empty";
				if (kingIsAttacked(DefaultBoard, 'w') == false) {
					validMoves[xPosition][yPosition - 1] = true;
				}
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition + 1;
				DefaultBoard.board[xPosition][yPosition] = "White King";
				DefaultBoard.board[xPosition][yPosition - 1] = temp;
			}
		}
		//Checking one left to the king so it can't bo on the far left
		if (xPosition != 0) {

			pieceInTheWay.setValues(board[xPosition - 1][yPosition]);
			if (pieceInTheWay.colour == 'b' || pieceInTheWay.key == 6) {
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition - 1;
				temp = board[xPosition - 1][yPosition];
				DefaultBoard.board[xPosition - 1][yPosition] = DefaultBoard.board[xPosition][yPosition];
				DefaultBoard.board[xPosition][yPosition] = "Empty";
				if (kingIsAttacked(DefaultBoard, 'w') == false) {
					validMoves[xPosition - 1][yPosition] = true;
				}
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition + 1;
				DefaultBoard.board[xPosition][yPosition] = "White King";
				DefaultBoard.board[xPosition - 1][yPosition] = temp;
			}
		}
		//Checking one above to the king so it can't be on the top row.
		if (yPosition != 7) {

			pieceInTheWay.setValues(board[xPosition][yPosition + 1]);
			if (pieceInTheWay.colour == 'b' || pieceInTheWay.key == 6) {
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition + 1;
				temp = board[xPosition][yPosition + 1];
				DefaultBoard.board[xPosition][yPosition + 1] = DefaultBoard.board[xPosition][yPosition];
				DefaultBoard.board[xPosition][yPosition] = "Empty";
				if (kingIsAttacked(DefaultBoard, 'w') == false) {
					validMoves[xPosition][yPosition + 1] = true;
				}
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition - 1;
				DefaultBoard.board[xPosition][yPosition] = "White King";
				DefaultBoard.board[xPosition][yPosition + 1] = temp;
			}
		}
		//Checking if the King is in the top right corner. If it isn't, we can check up and to the right of it.
		if (xPosition != 7 && yPosition != 7) {
			pieceInTheWay.setValues(board[xPosition + 1][yPosition + 1]);
			if (pieceInTheWay.colour == 'b' || pieceInTheWay.key == 6) {
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition + 1;
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition + 1;
				temp = board[xPosition + 1][yPosition + 1];
				DefaultBoard.board[xPosition + 1][yPosition + 1] = DefaultBoard.board[xPosition][yPosition];
				DefaultBoard.board[xPosition][yPosition] = "Empty";
				if (kingIsAttacked(DefaultBoard, 'w') == false) {
					validMoves[xPosition + 1][yPosition + 1] = true;
				}
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition - 1;
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition - 1;
				DefaultBoard.board[xPosition][yPosition] = "White King";
				DefaultBoard.board[xPosition + 1][yPosition + 1] = temp;
			}
		}
		//Checking if the King is in the bottom right corner. If it isn't, we can check down and to the right of it.
		if (xPosition != 7 && yPosition != 0) {
			pieceInTheWay.setValues(board[xPosition + 1][yPosition - 1]);
			if (pieceInTheWay.colour == 'b' || pieceInTheWay.key == 6) {
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition + 1;
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition - 1;
				temp = board[xPosition + 1][yPosition - 1];
				DefaultBoard.board[xPosition + 1][yPosition - 1] = DefaultBoard.board[xPosition][yPosition];
				DefaultBoard.board[xPosition][yPosition] = "Empty";
				if (kingIsAttacked(DefaultBoard, 'w') == false) {
					validMoves[xPosition + 1][yPosition - 1] = true;
				}
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition - 1;
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition + 1;
				DefaultBoard.board[xPosition][yPosition] = "White King";
				DefaultBoard.board[xPosition + 1][yPosition - 1] = temp;
			}
		}
		//Checking if the King is in the bottom left corner. If it isn't, we can check down and to the left of it.
		if (xPosition != 0 && yPosition != 0) {
			pieceInTheWay.setValues(board[xPosition - 1][yPosition - 1]);
			if (pieceInTheWay.colour == 'b' || pieceInTheWay.key == 6) {
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition - 1;
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition - 1;
				temp = board[xPosition - 1][yPosition - 1];
				DefaultBoard.board[xPosition - 1][yPosition - 1] = DefaultBoard.board[xPosition][yPosition];
				DefaultBoard.board[xPosition][yPosition] = "Empty";
				if (kingIsAttacked(DefaultBoard, 'w') == false) {
					validMoves[xPosition - 1][yPosition - 1] = true;
				}
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition + 1;
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition + 1;
				DefaultBoard.board[xPosition][yPosition] = "White King";
				DefaultBoard.board[xPosition - 1][yPosition - 1] = temp;
			}
		}
		//Checking if the King is in the top left corner. If it isn't, we can check up and to the left of it.
		if (xPosition != 0 && yPosition != 7) {
			pieceInTheWay.setValues(board[xPosition - 1][yPosition + 1]);
			if (pieceInTheWay.colour == 'b' || pieceInTheWay.key == 6) {
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition - 1;
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition + 1;
				temp = board[xPosition - 1][yPosition + 1];
				DefaultBoard.board[xPosition - 1][yPosition + 1] = DefaultBoard.board[xPosition][yPosition];
				DefaultBoard.board[xPosition][yPosition] = "Empty";
				if (kingIsAttacked(DefaultBoard, 'w') == false) {
					validMoves[xPosition - 1][yPosition + 1] = true;
				}
				DefaultBoard.whiteKingXPosition = DefaultBoard.whiteKingXPosition + 1;
				DefaultBoard.whiteKingYPosition = DefaultBoard.whiteKingYPosition - 1;
				DefaultBoard.board[xPosition][yPosition] = "White King";
				DefaultBoard.board[xPosition - 1][yPosition + 1] = temp;
			}
		}
	}
	//Next is the Black King.
	else if (key == 5 && colour == 'w')
	{

	//Checking one right to the king so it can't be on the far right side.
	if (xPosition != 7) {

		pieceInTheWay.setValues(board[xPosition + 1][yPosition]);
		if (pieceInTheWay.colour == 'w' || pieceInTheWay.key == 6) {
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition + 1;
			temp = board[xPosition + 1][yPosition];
			DefaultBoard.board[xPosition + 1][yPosition] = DefaultBoard.board[xPosition][yPosition];
			DefaultBoard.board[xPosition][yPosition] = "Empty";
			if (kingIsAttacked(DefaultBoard, 'b') == false) {
				validMoves[xPosition + 1][yPosition] = true;
			}
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition - 1;
			DefaultBoard.board[xPosition][yPosition] = "Black King";
			DefaultBoard.board[xPosition + 1][yPosition] = temp;
		}

	}
	//Checking one below to the king so it can't be on the bottom row.
	if (yPosition != 0) {

		pieceInTheWay.setValues(board[xPosition][yPosition - 1]);
		if (pieceInTheWay.colour == 'w' || pieceInTheWay.key == 6) {
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition - 1;
			temp = board[xPosition][yPosition - 1];
			DefaultBoard.board[xPosition][yPosition - 1] = DefaultBoard.board[xPosition][yPosition];
			DefaultBoard.board[xPosition][yPosition] = "Empty";
			if (kingIsAttacked(DefaultBoard, 'b') == false) {
				validMoves[xPosition][yPosition - 1] = true;
			}
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition + 1;
			DefaultBoard.board[xPosition][yPosition] = "Black King";
			DefaultBoard.board[xPosition][yPosition - 1] = temp;
		}
	}
	//Checking one left to the king so it can't bo on the far left
	if (xPosition != 0) {

		pieceInTheWay.setValues(board[xPosition - 1][yPosition]);
		if (pieceInTheWay.colour == 'w' || pieceInTheWay.key == 6) {
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition - 1;
			temp = board[xPosition - 1][yPosition];
			DefaultBoard.board[xPosition - 1][yPosition] = DefaultBoard.board[xPosition][yPosition];
			DefaultBoard.board[xPosition][yPosition] = "Empty";
			if (kingIsAttacked(DefaultBoard, 'b') == false) {
				validMoves[xPosition - 1][yPosition] = true;
			}
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition + 1;
			DefaultBoard.board[xPosition][yPosition] = "Black King";
			DefaultBoard.board[xPosition - 1][yPosition] = temp;
		}
	}
	//Checking one above to the king so it can't be on the top row.
	if (yPosition != 7) {

		pieceInTheWay.setValues(board[xPosition][yPosition + 1]);
		if (pieceInTheWay.colour == 'w' || pieceInTheWay.key == 6) {
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition + 1;
			temp = board[xPosition][yPosition + 1];
			DefaultBoard.board[xPosition][yPosition + 1] = DefaultBoard.board[xPosition][yPosition];
			DefaultBoard.board[xPosition][yPosition] = "Empty";
			if (kingIsAttacked(DefaultBoard, 'b') == false) {
				validMoves[xPosition][yPosition + 1] = true;
			}
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition - 1;
			DefaultBoard.board[xPosition][yPosition] = "Black King";
			DefaultBoard.board[xPosition][yPosition + 1] = temp;
		}
	}
	//Checking if the King is in the top right corner. If it isn't, we can check up and to the right of it.
	if (xPosition != 7 && yPosition != 7) {
		pieceInTheWay.setValues(board[xPosition + 1][yPosition + 1]);
		if (pieceInTheWay.colour == 'w' || pieceInTheWay.key == 6) {
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition + 1;
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition + 1;
			temp = board[xPosition + 1][yPosition + 1];
			DefaultBoard.board[xPosition + 1][yPosition + 1] = DefaultBoard.board[xPosition][yPosition];
			DefaultBoard.board[xPosition][yPosition] = "Empty";
			if (kingIsAttacked(DefaultBoard, 'b') == false) {
				validMoves[xPosition + 1][yPosition + 1] = true;
			}
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition - 1;
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition - 1;
			DefaultBoard.board[xPosition][yPosition] = "Black King";
			DefaultBoard.board[xPosition + 1][yPosition + 1] = temp;
		}
	}
	//Checking if the King is in the bottom right corner. If it isn't, we can check down and to the right of it.
	if (xPosition != 7 && yPosition != 0) {
		pieceInTheWay.setValues(board[xPosition + 1][yPosition - 1]);
		if (pieceInTheWay.colour == 'w' || pieceInTheWay.key == 6) {
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition + 1;
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition - 1;
			temp = board[xPosition + 1][yPosition - 1];
			DefaultBoard.board[xPosition + 1][yPosition - 1] = DefaultBoard.board[xPosition][yPosition];
			DefaultBoard.board[xPosition][yPosition] = "Empty";
			if (kingIsAttacked(DefaultBoard, 'b') == false) {
				validMoves[xPosition + 1][yPosition - 1] = true;
			}
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition - 1;
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition + 1;
			DefaultBoard.board[xPosition][yPosition] = "Black King";
			DefaultBoard.board[xPosition + 1][yPosition - 1] = temp;
		}
	}
	//Checking if the King is in the bottom left corner. If it isn't, we can check down and to the left of it.
	if (xPosition != 0 && yPosition != 0) {
		pieceInTheWay.setValues(board[xPosition - 1][yPosition - 1]);
		if (pieceInTheWay.colour == 'w' || pieceInTheWay.key == 6) {
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition - 1;
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition - 1;
			temp = board[xPosition - 1][yPosition - 1];
			DefaultBoard.board[xPosition - 1][yPosition - 1] = DefaultBoard.board[xPosition][yPosition];
			DefaultBoard.board[xPosition][yPosition] = "Empty";
			if (kingIsAttacked(DefaultBoard, 'b') == false) {
				validMoves[xPosition - 1][yPosition - 1] = true;
			}
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition + 1;
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition + 1;
			DefaultBoard.board[xPosition][yPosition] = "Black King";
			DefaultBoard.board[xPosition - 1][yPosition - 1] = temp;
		}
	}
	//Checking if the King is in the top left corner. If it isn't, we can check up and to the left of it.
	if (xPosition != 0 && yPosition != 7) {
		pieceInTheWay.setValues(board[xPosition - 1][yPosition + 1]);
		if (pieceInTheWay.colour == 'w' || pieceInTheWay.key == 6) {
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition - 1;
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition + 1;
			temp = board[xPosition - 1][yPosition + 1];
			DefaultBoard.board[xPosition - 1][yPosition + 1] = DefaultBoard.board[xPosition][yPosition];
			DefaultBoard.board[xPosition][yPosition] = "Empty";
			if (kingIsAttacked(DefaultBoard, 'b') == false) {
				validMoves[xPosition - 1][yPosition + 1] = true;
			}
			DefaultBoard.blackKingXPosition = DefaultBoard.blackKingXPosition + 1;
			DefaultBoard.blackKingYPosition = DefaultBoard.blackKingYPosition - 1;
			DefaultBoard.board[xPosition][yPosition] = "Black King";
			DefaultBoard.board[xPosition - 1][yPosition + 1] = temp;
		}
	}
	}
}

bool PossibleMoves::kingIsAttacked(BoardSetup Board, char colourOfKing) {
	cout << "King is attacked has been run" << '\n';
	//This function checks whether the friendly king is in check.
	//This is necessary, as it will decide whether some moves are valid.
	//it will do this by checking if any enemy pieces are in the way.

	//Set pieceInTheWay to White pawn as default, will change.
	Pieces pieceInTheWay("White Pawn");
	string board[8][8] = {};

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[x][y] = Board.board[x][y];
		}
	}

	//Following displays board. Uncomment for testing purposes.
	/*for (int y = 7; y > -1; y--)
	{
		for (int x = 0; x < 8; x++)
		{
			cout << board[x][y] << ", ";
		}
		cout << '\n';
	}*/

	if (colourOfKing == 'w') {
		//Checking potential attack from a pawn first. We only need to do that if the king is on the 6th row or below.
		if (Board.whiteKingYPosition < 6) {
			if (Board.whiteKingXPosition < 1) {
				//ignore a potential attack from outside the board (we are checking the row left to the king)
			}
			else {
				pieceInTheWay.setValues(board[Board.whiteKingXPosition - 1][Board.whiteKingYPosition + 1]);
				if (pieceInTheWay.key == 0 && pieceInTheWay.colour == 'b') {
					return true;
				}
			}
			if (Board.whiteKingXPosition > 6) {
				//ignore a potential attack from outside the board (we are checking the row right to the king)
			}
			else {
				pieceInTheWay.setValues(board[Board.whiteKingXPosition + 1][Board.whiteKingYPosition + 1]);
				if (pieceInTheWay.key == 0 && pieceInTheWay.colour == 'b') {
					return true;
				}
			}
		}
		
		//Checking potential attack from a knight next.
		if (Board.whiteKingXPosition > 1 && Board.whiteKingYPosition < 7) {
			//Check 2 left and 1 up first.
			pieceInTheWay.setValues(board[Board.whiteKingXPosition - 2][Board.whiteKingYPosition + 1]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'b') {
				return true;
			}
			
		} //Checking 1 left and 2 up next.
		if (Board.whiteKingXPosition > 0 && Board.whiteKingYPosition < 6) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition - 1][Board.whiteKingYPosition + 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'b') {
				return true;
			}
		} //Checking 1 right and 2 up next.
		if (Board.whiteKingXPosition < 7 && Board.whiteKingYPosition < 6) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition + 1][Board.whiteKingYPosition + 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'b') {
				return true;
			}
		} //Checking 2 right and 1 up next.
		if (Board.whiteKingXPosition < 6 && Board.whiteKingYPosition < 7) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition + 2][Board.whiteKingYPosition + 1]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'b') {
				return true;
			}
		} //Checking 2 right and 1 down next.
		if (Board.whiteKingXPosition < 6 && Board.whiteKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition + 2][Board.whiteKingYPosition - 1]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'b') {
				return true;
			}
		} //Checking 1 right and 2 down next.
		if (Board.whiteKingXPosition < 7 && Board.whiteKingYPosition > 1) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition + 1][Board.whiteKingYPosition - 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'b') {
				return true;
			}
		} //Checking 1 left and 2 down next
		if (Board.whiteKingXPosition > 0 && Board.whiteKingYPosition > 1) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition - 1][Board.whiteKingYPosition - 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'b') {
				return true;
			}
		} //Finally checking 2 left and 1 down.
		if (Board.whiteKingXPosition > 1 && Board.whiteKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition + 1][Board.whiteKingYPosition - 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'b') {
				return true;
			}
		}

		//Next lets do the Bishop and diagonals of the Queen whilst we are at it.
		//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
		//This reuses some of the code from the PossibleMoves constructor, but it is slightly different so I couldn't reuse it (e.g as a function).
		int i = 1;
		bool pathIsClear = true;

		while (Board.whiteKingXPosition - i >= 0 && Board.whiteKingYPosition + i <= 7 && pathIsClear == true) {

			if (board[Board.whiteKingXPosition - i][Board.whiteKingYPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.whiteKingXPosition - i][Board.whiteKingYPosition + i]);
				//If there is a black bishop on the diagonal, the square is attacked.
				if (pieceInTheWay.key == 2 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				//If there is a black queen on the diagonal, the square is attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				pathIsClear = false;
			}
			else
			{
				
			}
			i++;
		}
		
		i = 1;
		pathIsClear = true;
		//Next direction up and right. ALso we need to reset i and pathIsClear variable after every while loop (done in lines above).
		while (Board.whiteKingXPosition + i <= 7 && Board.whiteKingYPosition + i <= 7 && pathIsClear == true) {

			if (board[Board.whiteKingXPosition + i][Board.whiteKingYPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.whiteKingXPosition + i][Board.whiteKingYPosition + i]);
				//If there is a black bishop on the diagonal, the square is attacked.
				if (pieceInTheWay.key == 2 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				//If there is a black queen on the diagonal, the square is attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				pathIsClear = false;
			}
			else
			{

			}
			i++;
		}

		//Next direction is diagonally down and right. Again resetting i and pathIsClear variables.
		i = 1;
		pathIsClear = true;
		while (Board.whiteKingXPosition + i <= 7 && Board.whiteKingYPosition - i >= 0 && pathIsClear == true) {

			if (board[Board.whiteKingXPosition + i][Board.whiteKingYPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.whiteKingXPosition + i][Board.whiteKingYPosition - i]);
				//If there is a black bishop on the diagonal, the square is attacked.
				if (pieceInTheWay.key == 2 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				//If there is a black queen on the diagonal, the square is attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				pathIsClear = false;
			}
			else
			{

			}
			i++;
		}

		//And the final direction is diagonally down and left.
		i = 1;
		pathIsClear = true;
		while (Board.whiteKingXPosition - i >= 0 && Board.whiteKingYPosition - i >= 0 && pathIsClear == true) {

			if (board[Board.whiteKingXPosition - i][Board.whiteKingYPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.whiteKingXPosition - i][Board.whiteKingYPosition - i]);
				//If there is a black bishop on the diagonal, the square is attacked.
				if (pieceInTheWay.key == 2 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				//If there is a black queen on the diagonal, the square is attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				pathIsClear = false;
			}
			else
			{

			}
			i++;
		}

		//And with that validation for the diagonals is done. Next is to do the straight lines of rooks and queens.
		//lets do straight up first
		i = 1;
		pathIsClear = true;
		while (Board.whiteKingYPosition + i <= 7 && pathIsClear)
		{
			if (board[Board.whiteKingXPosition][Board.whiteKingYPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.whiteKingXPosition][Board.whiteKingYPosition + i]);
				//If there is a black rook in line with the square, it is being attacked.
				if (pieceInTheWay.key == 3 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				//If there is a black queen in line with the square, it is being attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'b')
				{
					return true;			
				}
				pathIsClear = false;
			}

			i++;
		}

		//Same but for straight right.
		i = 1;
		pathIsClear = true;
		while (Board.whiteKingXPosition + i <= 7 && pathIsClear)
		{
			if (board[Board.whiteKingXPosition + i][Board.whiteKingYPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.whiteKingXPosition + i][Board.whiteKingYPosition]);
				//If there is a black rook in line with the square, it is being attacked.
				if (pieceInTheWay.key == 3 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				//If there is a black queen in line with the square, it is being attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				pathIsClear = false;
			}

			i++;
		}

		//Same again but for straight down
		i = 1;
		pathIsClear = true;
		while (Board.whiteKingYPosition - i >= 0 && pathIsClear)
		{
			if (board[Board.whiteKingXPosition][Board.whiteKingYPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.whiteKingXPosition + i][Board.whiteKingYPosition]);
				//If there is a black rook in line with the square, it is being attacked.
				if (pieceInTheWay.key == 3 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				//If there is a black queen in line with the square, it is being attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				pathIsClear = false;
			}

			i++;
		}

		//Same but for straight left.
		i = 1;
		pathIsClear = true;
		while (Board.whiteKingXPosition - i >= 0 && pathIsClear)
		{
			if (board[Board.whiteKingXPosition - i][Board.whiteKingYPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.whiteKingXPosition - i][Board.whiteKingYPosition]);
				//If there is a black rook in line with the square, it is being attacked.
				if (pieceInTheWay.key == 3 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				//If there is a black queen in line with the square, it is being attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'b')
				{
					return true;
				}
				pathIsClear = false;
			}

			i++;
		}

		//Finally we need to check if the enemy king is guarding a square.

		//Lets start with directly above the king.
		if (Board.whiteKingYPosition < 7) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition][Board.whiteKingYPosition + 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do up and right
		if (Board.whiteKingXPosition < 7 && Board.whiteKingYPosition < 7) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition + 1][Board.whiteKingYPosition + 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do right
		if (Board.whiteKingXPosition < 7) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition + 1][Board.whiteKingYPosition]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do right and down
		if (Board.whiteKingXPosition < 7 && Board.whiteKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition + 1][Board.whiteKingYPosition - 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do down
		if (Board.whiteKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition][Board.whiteKingYPosition - 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do down and left
		if (Board.whiteKingXPosition > 0 && Board.whiteKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition - 1][Board.whiteKingYPosition - 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do left
		if (Board.whiteKingXPosition > 0) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition - 1][Board.whiteKingYPosition]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do left and up
		if (Board.whiteKingXPosition > 0 && Board.whiteKingYPosition < 7) {
			pieceInTheWay.setValues(board[Board.whiteKingXPosition - 1][Board.whiteKingYPosition + 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}


	} else if (colourOfKing == 'b') {
		//Checking potential attack from a pawn first. We only need to do that if the king is on the 6th row or below.
		if (Board.blackKingYPosition < 6) {
			if (Board.blackKingXPosition < 1) {
				//ignore a potential attack from outside the board (we are checking the row left to the king)
			}
			else {
				pieceInTheWay.setValues(board[Board.blackKingXPosition - 1][Board.blackKingYPosition + 1]);
				if (pieceInTheWay.key == 0 && pieceInTheWay.colour == 'w') {
					return true;
				}
			}
			if (Board.blackKingXPosition > 6) {
				//ignore a potential attack from outside the board (we are checking the row right to the king)
			}
			else {
				pieceInTheWay.setValues(board[Board.blackKingXPosition + 1][Board.blackKingYPosition + 1]);
				if (pieceInTheWay.key == 0 && pieceInTheWay.colour == 'w') {
					return true;
				}
			}
		}

		//Checking potential attack from a knight next.
		if (Board.blackKingXPosition > 1 && Board.blackKingYPosition < 7) {
			//Check 2 left and 1 up first.
			pieceInTheWay.setValues(board[Board.blackKingXPosition - 2][Board.blackKingYPosition + 1]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'w') {
				return true;
			}

		} //Checking 1 left and 2 up next.
		if (Board.blackKingXPosition > 0 && Board.blackKingYPosition < 6) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition - 1][Board.blackKingYPosition + 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'w') {
				return true;
			}
		} //Checking 1 right and 2 up next.
		if (Board.blackKingXPosition < 7 && Board.blackKingYPosition < 6) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition + 1][Board.blackKingYPosition + 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'w') {
				return true;
			}
		} //Checking 2 right and 1 up next.
		if (Board.blackKingXPosition < 6 && Board.blackKingYPosition < 7) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition + 2][Board.blackKingYPosition + 1]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'w') {
				return true;
			}
		} //Checking 2 right and 1 down next.
		if (Board.blackKingXPosition < 6 && Board.blackKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition + 2][Board.blackKingYPosition - 1]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'w') {
				return true;
			}
		} //Checking 1 right and 2 down next.
		if (Board.blackKingXPosition < 7 && Board.blackKingYPosition > 1) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition + 1][Board.blackKingYPosition - 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'w') {
				return true;
			}
		} //Checking 1 left and 2 down next
		if (Board.blackKingXPosition > 0 && Board.blackKingYPosition > 1) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition - 1][Board.blackKingYPosition - 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'w') {
				return true;
			}
		} //Finally checking 2 left and 1 down.
		if (Board.blackKingXPosition > 1 && Board.blackKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition + 1][Board.blackKingYPosition - 2]);
			if (pieceInTheWay.key == 1 && pieceInTheWay.colour == 'w') {
				return true;
			}
		}

		//Next lets do the Bishop and diagonals of the Queen whilst we are at it.
		//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
		//This reuses some of the code from the PossibleMoves constructor, but it is slightly different so I couldn't reuse it (e.g as a function).
		int i = 1;
		bool pathIsClear = true;

		while (Board.blackKingXPosition - i >= 0 && Board.blackKingYPosition + i <= 7 && pathIsClear == true) {

			if (board[Board.blackKingXPosition - i][Board.blackKingYPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.blackKingXPosition - i][Board.blackKingYPosition + i]);
				//If there is a white bishop on the diagonal, the square is attacked.
				if (pieceInTheWay.key == 2 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				//If there is a white queen on the diagonal, the square is attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				pathIsClear = false;
			}
			else
			{

			}
			i++;
		}

		i = 1;
		pathIsClear = true;
		//Next direction up and right. ALso we need to reset i and pathIsClear variable after every while loop (done in lines above).
		while (Board.blackKingXPosition + i <= 7 && Board.blackKingYPosition + i <= 7 && pathIsClear == true) {

			if (board[Board.blackKingXPosition + i][Board.blackKingYPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.blackKingXPosition + i][Board.blackKingYPosition + i]);
				//If there is a white bishop on the diagonal, the square is attacked.
				if (pieceInTheWay.key == 2 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				//If there is a white queen on the diagonal, the square is attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				pathIsClear = false;
			}
			else
			{

			}
			i++;
		}

		//Next direction is diagonally down and right. Again resetting i and pathIsClear variables.
		i = 1;
		pathIsClear = true;
		while (Board.blackKingXPosition + i <= 7 && Board.blackKingYPosition - i >= 0 && pathIsClear == true) {

			if (board[Board.blackKingXPosition + i][Board.blackKingYPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.blackKingXPosition + i][Board.blackKingYPosition - i]);
				//If there is a white bishop on the diagonal, the square is attacked.
				if (pieceInTheWay.key == 2 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				//If there is a white queen on the diagonal, the square is attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				pathIsClear = false;
			}
			else
			{

			}
			i++;
		}

		//And the final direction is diagonally down and left.
		i = 1;
		pathIsClear = true;
		while (Board.blackKingXPosition - i >= 0 && Board.blackKingYPosition - i >= 0 && pathIsClear == true) {

			if (board[Board.blackKingXPosition - i][Board.blackKingYPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.blackKingXPosition - i][Board.blackKingYPosition - i]);
				//If there is a white bishop on the diagonal, the square is attacked.
				if (pieceInTheWay.key == 2 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				//If there is a white queen on the diagonal, the square is attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				pathIsClear = false;
			}
			else
			{

			}
			i++;
		}

		//And with that validation for the diagonals is done. Next is to do the straight lines of rooks and queens.
		//lets do straight up first
		i = 1;
		pathIsClear = true;
		while (Board.blackKingYPosition + i <= 7 && pathIsClear)
		{
			if (board[Board.blackKingXPosition][Board.blackKingYPosition + i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.blackKingXPosition][Board.blackKingYPosition + i]);
				//If there is a white rook in line with the square, it is being attacked.
				if (pieceInTheWay.key == 3 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				//If there is a white queen in line with the square, it is being attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				pathIsClear = false;
			}

			i++;
		}

		//Same but for straight right.
		i = 1;
		pathIsClear = true;
		while (Board.blackKingXPosition + i <= 7 && pathIsClear)
		{
			if (board[Board.blackKingXPosition + i][Board.blackKingYPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.blackKingXPosition + i][Board.blackKingYPosition]);
				//If there is a white rook in line with the square, it is being attacked.
				if (pieceInTheWay.key == 3 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				//If there is a white queen in line with the square, it is being attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				pathIsClear = false;
			}

			i++;
		}

		//Same again but for straight down
		i = 1;
		pathIsClear = true;
		while (Board.blackKingYPosition - i >= 0 && pathIsClear)
		{
			if (board[Board.blackKingXPosition][Board.blackKingYPosition - i] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.blackKingXPosition + i][Board.blackKingYPosition]);
				//If there is a white rook in line with the square, it is being attacked.
				if (pieceInTheWay.key == 3 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				//If there is a white queen in line with the square, it is being attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				pathIsClear = false;
			}

			i++;
		}

		//Same but for straight left.
		i = 1;
		pathIsClear = true;
		while (Board.blackKingXPosition - i >= 0 && pathIsClear)
		{
			if (board[Board.blackKingXPosition - i][Board.blackKingYPosition] != "Empty")
			{
				pieceInTheWay.setValues(board[Board.blackKingXPosition - i][Board.blackKingYPosition]);
				//If there is a white rook in line with the square, it is being attacked.
				if (pieceInTheWay.key == 3 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				//If there is a white queen in line with the square, it is being attacked.
				else if (pieceInTheWay.key == 4 && pieceInTheWay.colour == 'w')
				{
					return true;
				}
				pathIsClear = false;
			}

			i++;
		}

		//Finally we need to check if the enemy king is guarding a square.

		//Lets start with directly above the king.
		if (Board.blackKingYPosition < 7) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition][Board.blackKingYPosition + 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do up and right
		if (Board.blackKingXPosition < 7 && Board.blackKingYPosition < 7) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition + 1][Board.blackKingYPosition + 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do right
		if (Board.blackKingXPosition < 7) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition + 1][Board.blackKingYPosition]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do right and down
		if (Board.blackKingXPosition < 7 && Board.blackKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition + 1][Board.blackKingYPosition - 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do down
		if (Board.blackKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition][Board.blackKingYPosition - 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do down and left
		if (Board.blackKingXPosition > 0 && Board.blackKingYPosition > 0) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition - 1][Board.blackKingYPosition - 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do left
		if (Board.blackKingXPosition > 0) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition - 1][Board.blackKingYPosition]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}

		//Next lets do left and up
		if (Board.blackKingXPosition > 0 && Board.blackKingYPosition < 7) {
			pieceInTheWay.setValues(board[Board.blackKingXPosition - 1][Board.blackKingYPosition + 1]);
			if (pieceInTheWay.key == 5) {
				return true;
			}
		}
	}
	return false;
}
