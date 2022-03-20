#pragma once

#include <iostream>
#include <string>
#include"BoardSetup.h" 
#include"Pieces.h"

using std::cout;
using std::endl;
using std::string;

class PossibleMoves {
public:
	bool validMoves[8][8];

	PossibleMoves();
	PossibleMoves(BoardSetup DefaultBoard, Pieces TestData, int xPosition, int yPosition);

	bool kingIsAttacked(BoardSetup Board, char colourOfKing);
};
