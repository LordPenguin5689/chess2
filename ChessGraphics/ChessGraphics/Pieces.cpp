#include"BoardSetup.h"
#include"Pieces.h"

#include <iostream>
#include <string>

Pieces::Pieces(string name) {
	// Constructor takes the name of every piece and convert it into a key and colour. Makes it easy to understand what everything represents.
	//The following line uses the .find function to check if the string contains a phrase (in this case white). the "!= std::string::npos" is voodoo. Do not mess with.
	if (name.find("White") != std::string::npos) {
		colour = 'w';
	}
	else if (name.find("Black") != std::string::npos) {
		colour = 'b';
	}
	else {
		colour = 'n';
		cout << "Error in generating colour. Defaulting to null value (n)" << '\n';
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
		cout << "Error in generating key. Defaulting to 0." << '\n';
	}
}

//Method that outputs the key and colour of a Piece object
void Pieces::OutputProperties() {
	cout << key << '\n';
	cout << colour << '\n';
}

//Object to set values for key and colour of a piece.
void Pieces::setValues(string name) {
	if (name.find("White") != std::string::npos) {
		colour = 'w';
	}
	else if (name.find("Black") != std::string::npos) {
		colour = 'b';
	}
	else {
		colour = 'n';
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
	}
	else
	{
		key = 6;
		cout << "Error in generating key. Defaulting to 6." << endl;
	}

}