#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class BoardSetup {
public:
	string board[8][8];
	int whiteKingXPosition;
	int whiteKingYPosition;
	int blackKingXPosition;
	int blackKingYPosition;
	bool player1sTurn;

	BoardSetup();
	BoardSetup(string fen);

	string ReturnPieceName(int xPosition, int yPosition);
};