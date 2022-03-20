#pragma once

#include <iostream>
#include <string>
#include"BoardSetup.h" 


using std::cout;
using std::endl;
using std::string;

class Pieces {
public:
	string name;
	int key;
	char colour;

	Pieces(string name);
	void OutputProperties();
	void setValues(string name);

};