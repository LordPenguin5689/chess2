#include <iostream>
#include <string>

// The following 2 lines just allow me to just write "cout" and "endl" instead of "std::cout" and "std::endl". This is just to make it easier to read and write.
using std::cout;
using std::endl;
using std::string;

// This class defines a number for each piece so that they can be stored in an array. Black pieces will have values of the piece plus 7, therefore if a piece number is < 7 it is white.


class Pieces {
	public:
		//name is name of piece. key is the value which I will use to represent the pieces. More on it below. Colour will either be 'b' for black or 'w' for white.
		string name;
		int key;
		char colour;

		

		Pieces(string name) {
			// Constructor takes the name of every piece and convert it into a key and colour. Makes it easy to understand what everything represents.
			//The following line uses the .find function to check if the string contains a phrase (in this case white). the "!= std::string::npos" is voodoo. Do not mess with.
			if (name.find("White") != std::string::npos) {
				colour = 'w';
			}
			else if (name.find("Black") != std::string::npos) {
				colour = 'b';
			}
			else {
				colour = 'w';
				cout << "Error in generating colour. Defaulting to white." << endl;
			}

			if (name.find("Pawn", 0) != std::string::npos) {
				key = 0;
			}
			else if (name.find("Knight", 0) != std::string::npos) {
				key = 1;
			}
			else if (name.find("Bishop", 0) != std::string::npos) {
				key = 2;
			}
			else if (name.find("Rook", 0) != std::string::npos) {
				key = 3;
			}
			else if (name.find("Queen", 0) != std::string::npos) {
				key = 4;
			}
			else if (name.find("King", 0) != std::string::npos) {
				key = 5;
			}
			else if (name.find("Empty") != std::string::npos) {
				key = 6;
				colour = 'n';
			}
			else
			{
				key = 0;
				cout << "Error in generating key. Defaulting to 0." << endl;
			}
		}

		// little function to output properties of a piece to check it works.
		void OutputProperties() {
			cout << key << endl;
			cout << colour << endl;
		}


};

class BoardSetup {
public:
	string board[8][8];

	int ReturnRow() {
		
	}

	string ReturnPieceName(int xPosition, int yPosition) {
		return board[xPosition][yPosition];
	}

	//The following is a default constructor that will setup the normal board for beginning a game of chess
	BoardSetup() {
		board[0][0] = "White Rook";
		board[1][0] = "White Knight";
		board[2][0] = "White Bishop";
		board[3][0] = "White Queen";
		board[4][0] = "White King";
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
		board[5][7] = "Black Bishop";
		board[6][7] = "Black Knight";
		board[7][7] = "Black Rook";

	}

	//The following is a constructor that will take in a FEN and create a board from it.
	BoardSetup(string fen) {
		//This first point finds where hashes occur in the FEN so we can split up the pieces by row later.
		int findForwardSlashPostion = 0;
		int forwardSlashPositions[9];
		forwardSlashPositions[0] = -2;


		for (int i = 1; i < 8; i++) {
			findForwardSlashPostion = fen.find_first_of("/", findForwardSlashPostion+1);
			forwardSlashPositions[i] = findForwardSlashPostion;
		}
		forwardSlashPositions[8] = (fen.find_first_of(" ", forwardSlashPositions[7]+2)) + 1;
		



		//The following generates FEN in the array
		int count = 0;
		for (int y = 0; y < 8; y++) {
			for (int x = forwardSlashPositions[y] + 2; x < forwardSlashPositions[y + 1] - 1; x++) {
				board[count][y] = fen[x];
				count++;
			}
			count = 0;
		}


		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				cout << board[x][y] + ", ";
			}
			cout << endl;
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
					// = 3	

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

		cout << endl;
		cout << endl;

		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				cout << board[x][y] + ", ";
			}
			cout << endl;
		}


	}
};

//Class which will use a 2d boolean array to show all the possible moves for a piece.
class PossibleMoves {
	public:
		bool validMoves[8][8];

		PossibleMoves(int key, char colour, int xPosition, int yPosition) {

			BoardSetup DefaultBoard;
			string board[8][8];

			for (int y = 0; y < 8; y++)
			{
				for (int x = 0; x < 8; x++)
				{
					board[x][y] = DefaultBoard.board[x][y];
				}
			}


			


			//Start with white pawn
			if (key == 0 && colour == 'w') {
				//If pawn is on the left most side the only possible move is diagonally right and up.
				//Also there is no need to check y position as a pawn cannot be on the 8th row or it will promote.
				if (xPosition == 0) {
					validMoves[1][yPosition + 1] = true;
				}
				else if (xPosition == 7) {
					validMoves[6][yPosition + 1] = true;
				}
				else
				{
					validMoves[xPosition - 1][yPosition + 1] = true;
					validMoves[xPosition + 1][yPosition + 1] = true;
				}
			}
			//Next is Black pawn so it is just the same but y position goes down
			else if (key == 0 && colour == 'b') {
				if (xPosition == 0) {
					validMoves[1][yPosition - 1] = true;
				}
				else if (xPosition == 7) {
					validMoves[6][yPosition - 1] = true;
				}
				else
				{
					validMoves[xPosition - 1][yPosition - 1] = true;
					validMoves[xPosition + 1][yPosition - 1] = true;
				}
			}
			//Next lets program the white bishop because I am not in the mood to do the knight just yet.
			else if (key == 2 && colour == 'w') {

				//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
				int i = 1;
				bool pathIsClear = false;

				while (xPosition - i >= 0 && yPosition + i <= 7 && pathIsClear == true) {
					
					if (board[xPosition - i][yPosition + i] != "Empty") 
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition + i]);
						if (pieceInTheWay.key == 'b')
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

					if (board[xPosition + i][yPosition + i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition + i]);
						if (pieceInTheWay.key == 'b')
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

					if (board[xPosition + i][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition - i]);
						if (pieceInTheWay.key == 'b')
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

				//And the final direction is diagonally down and left.
				i = 1;
				pathIsClear = true;
				while (xPosition - i >= 0 && yPosition - i >= 0 && pathIsClear == true) {

					if (board[xPosition - i][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition - i]);
						if (pieceInTheWay.key == 'b')
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

				//The previous code does not account for checks, but I will write a function with line of sight of for the King which will run before move is validated.
			}
			//Same as the previous while loops for white bishops but for black ones.
			else if (key == 2 && colour == 'b') 
			{

			//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
			int i = 1;
			bool pathIsClear = false;

			while (xPosition - i >= 0 && yPosition + i <= 7 && pathIsClear == true) {

				if (board[xPosition - i][yPosition + i] != "Empty")
				{
					Pieces pieceInTheWay(board[xPosition - i][yPosition + i]);
					if (pieceInTheWay.key == 'w')
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

				if (board[xPosition + i][yPosition + i] != "Empty")
				{
					Pieces pieceInTheWay(board[xPosition + i][yPosition + i]);
					if (pieceInTheWay.key == 'w')
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

				if (board[xPosition + i][yPosition - i] != "Empty")
				{
					Pieces pieceInTheWay(board[xPosition + i][yPosition - i]);
					if (pieceInTheWay.key == 'w')
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

				if (board[xPosition - i][yPosition - i] != "Empty")
				{
					Pieces pieceInTheWay(board[xPosition - i][yPosition - i]);
					if (pieceInTheWay.key == 'w')
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
			if (key == 3 && colour == 'w') 
			{

				//lets do straight up first
				int i = 1;
				bool pathIsClear = true;
				while (yPosition + i<= 7 && pathIsClear) 
				{
					if (board[xPosition][yPosition + i] != "Empty") 
					{
						Pieces pieceInTheWay(board[xPosition][yPosition + i]);
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
					if (board[xPosition + i][yPosition] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition]);
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
					if (board[xPosition][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition][yPosition - i]);
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
					if (board[xPosition - i][yPosition] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition]);
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
			if (key == 3 && colour == 'b')
			{

				//lets do straight up first
				int i = 1;
				bool pathIsClear = true;
				while (yPosition + i <= 7 && pathIsClear)
				{
					if (board[xPosition][yPosition + i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition][yPosition + i]);
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
					if (board[xPosition + i][yPosition] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition]);
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
					if (board[xPosition][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition][yPosition - i]);
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
					if (board[xPosition - i][yPosition] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition]);
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
			if (key == 1 && colour == 'w') 
			{
				//I am going to implement this almost manually. If this makes you cringe that is okay. I don't have the brain power right now to implement a more efficient system.
				//I may come back to this to increase the efficiency.
				//First lets go 2 left and 1 up
				if (xPosition - 2 >= 0 && yPosition + 1 <= 7)
					//Now to check if a piece is in the position we want to jump to.
					if (board[xPosition - 2][yPosition + 1] != "Empty") 
					{
						Pieces pieceInTheWay(board[xPosition - 2][yPosition + 1]);
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
						Pieces pieceInTheWay(board[xPosition - 1][yPosition + 2]);
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
						Pieces pieceInTheWay(board[xPosition + 1][yPosition + 2]);
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
						Pieces pieceInTheWay(board[xPosition + 2][yPosition + 1]);
						//Now check if piece is white.
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
						Pieces pieceInTheWay(board[xPosition + 2][yPosition - 1]);
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
						Pieces pieceInTheWay(board[xPosition + 1][yPosition - 2]);
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
						Pieces pieceInTheWay(board[xPosition - 1][yPosition - 2]);
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
						Pieces pieceInTheWay(board[xPosition - 1][yPosition - 2]);
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

			//Next is Black Knight
			if (key == 1 && colour == 'b')
			{
				//I am going to implement this almost manually. If this makes you cringe that is okay. I don't have the brain power right now to implement a more efficient system.
				//I may come back to this to increase the efficiency.
				//First lets go 2 left and 1 up
				if (xPosition - 2 >= 0 && yPosition + 1 <= 7)
					//Now to check if a piece is in the position we want to jump to.
					if (board[xPosition - 2][yPosition + 1] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - 2][yPosition + 1]);
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
						Pieces pieceInTheWay(board[xPosition - 1][yPosition + 2]);
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
						Pieces pieceInTheWay(board[xPosition + 1][yPosition + 2]);
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
						Pieces pieceInTheWay(board[xPosition + 2][yPosition + 1]);
						//Now check if piece is black.
						if (pieceInTheWay.colour == 'w')
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
						Pieces pieceInTheWay(board[xPosition + 2][yPosition - 1]);
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
						Pieces pieceInTheWay(board[xPosition + 1][yPosition - 2]);
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
						Pieces pieceInTheWay(board[xPosition - 1][yPosition - 2]);
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
						Pieces pieceInTheWay(board[xPosition - 1][yPosition - 2]);
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


			//Next is to do the Queen. There is nothing new or interesting here, it is just a combination of the bishop and rook move validation.
			if (key == 4 && colour == 'w') {
				//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
				int i = 1;
				bool pathIsClear = false;

				while (xPosition - i >= 0 && yPosition + i <= 7 && pathIsClear == true) {

					if (board[xPosition - i][yPosition + i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition + i]);
						if (pieceInTheWay.key == 'b')
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

					if (board[xPosition + i][yPosition + i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition + i]);
						if (pieceInTheWay.key == 'b')
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

					if (board[xPosition + i][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition - i]);
						if (pieceInTheWay.key == 'b')
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

					if (board[xPosition - i][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition - i]);
						if (pieceInTheWay.key == 'b')
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
					if (board[xPosition][yPosition + i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition][yPosition + i]);
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
					if (board[xPosition + i][yPosition] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition]);
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
					if (board[xPosition][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition][yPosition - i]);
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
					if (board[xPosition - i][yPosition] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition]);
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
			if (key == 4 && colour == 'b') {

				//Lets do each of the 4 diagonals in one by one, starting with diagonally up and left.
				int i = 1;
				bool pathIsClear = false;

				while (xPosition - i >= 0 && yPosition + i <= 7 && pathIsClear == true) {

					if (board[xPosition - i][yPosition + i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition + i]);
						if (pieceInTheWay.key == 'w')
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

					if (board[xPosition + i][yPosition + i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition + i]);
						if (pieceInTheWay.key == 'w')
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

					if (board[xPosition + i][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition - i]);
						if (pieceInTheWay.key == 'w')
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

					if (board[xPosition - i][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition - i]);
						if (pieceInTheWay.key == 'w')
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
					if (board[xPosition][yPosition + i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition][yPosition + i]);
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
					if (board[xPosition + i][yPosition] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition + i][yPosition]);
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
					if (board[xPosition][yPosition - i] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition][yPosition - i]);
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
					if (board[xPosition - i][yPosition] != "Empty")
					{
						Pieces pieceInTheWay(board[xPosition - i][yPosition]);
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


		}
};








int main() {
	string PieceName = "White Knight";
	int count = 0;
	
	Pieces FetchingDataForTest1(PieceName);

	int key = FetchingDataForTest1.key;
	char colour = FetchingDataForTest1.colour;
	int xPosition = 1;
	int yPosition = 0;
	

	PossibleMoves arrayOfPossibleMoves(key, colour, xPosition, yPosition);
	
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			cout << std::boolalpha << arrayOfPossibleMoves.validMoves[x][y] << endl;
		}
	}
	
	
	
	// Values needed: int key, char colour, int xPosition, int yPosition, string board[8][8].
}