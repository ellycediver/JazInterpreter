#pragma once
////////////////////////////////////////////////////////////////
//	Description:This file contains the Variable class. This
//	will be used as a way of relating a variable name to a value
//	and use them during the program execution
////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

class Variable{
protected:
	string name;
	int value;
public:
	//Default Constructor
	Variable();

	//Constructor
	Variable(string name, int value);

	//Get the name of the variable
	string getName() { return name; };

	//Get the value of the variable
	int getValue() { return value; };

	//Assign the string name to the name of the variable
	void setName(string name);

	//Assing the int value to the value of the variable
	void setValue(int value);

};
