#include "Variable.h"
////////////////////////////////////////////////////////////////
//	Description:This file contains the Variable class. This
//	will be used as a way of relating a variable name to a value
//	and use them during the program execution
////////////////////////////////////////////////////////////////

//Default Constructor
Variable::Variable() {
	string name = "";
	int value = 0;

	this->name =  name;
	this->value =  value;
}

//Constructor
Variable::Variable(string name, int value) {
	this->name =  name;
	this->value =  value;
}

//Assign the string name to the name of the variable
void Variable::setName(string name) {
	this->name = name;
}

//Assing the int value to the value of the variable
void Variable::setValue(int value) {
	this->value = value;
}

