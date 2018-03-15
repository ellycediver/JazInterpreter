////////////////////////////////////////////////////////////////
//	Description:This file contains the implementation of the
//	functions performed by the jaz machine
////////////////////////////////////////////////////////////////
#include "Functions.h"
#include "SymbolTable.h"
#include "Variable.h"
using namespace std;

////////////////////////////////
///////STACK MANIPULATION///////
////////////////////////////////

//Pushes value to the machine stack
void push(string value) {
	MachineStack.top().push_back(stoi(value));
}

//Pushes the value of the passed variable on the machine stack.
//Searches for the variable in the list of variables within the scope and
//if found pushes its value into the machine stack
void rvalue(string variable) {
	//find if variable has already been declared
	bool found = false;
	for (size_t i = 0; i < readVariablePointer->size(); i++) {
		if (variable == readVariablePointer->at(i).getName()) {
			MachineStack.top().push_back(readVariablePointer->at(i).getValue());
			found = true;
			break;
		}
	}

	//if not found create variable
	if (!found) {
		Variable v;
		v.setName(variable);
		v.setValue(0);
		readVariablePointer->push_back(v);
		MachineStack.top().push_back(readVariablePointer->back().getValue());
	}
}

//Pushes the address of the variable indicated into the machine stack.
//Searches for the variable in the list of variables available in the
//scope and pushes it if found, or it creates a new variable if not
void lvalue(string variable) {
	//find if variable has already been declared
	bool found = false;
	for (size_t i = 0; i < writeVariablePointer->size(); i++) {
		if (variable == writeVariablePointer->at(i).getName()) {
			found = true;
			MachineStack.top().push_back(int(&(writeVariablePointer->at(i))));
			break;
		}
	}

	//if not found create variable
	if (!found) {
		Variable v;
		v.setName(variable);
		v.setValue(0);
		writeVariablePointer->push_back(v);
		MachineStack.top().push_back(int(&(writeVariablePointer->back())));
	}
}

//Pops the top value of the stack
void pop() {
	MachineStack.top().pop_back();
}

//Takes the value on top of the stack and places it into the location placed below it.
//It also pops both values from the stack
void colEquals() {
	int vValue = MachineStack.top().back();
	MachineStack.top().pop_back();
	int vAdress = MachineStack.top().back();
	MachineStack.top().pop_back();

	for (size_t i = 0; i < writeVariablePointer->size(); i++) {
		if (vAdress == int(&(writeVariablePointer->at(i)))) {
			writeVariablePointer->at(i).setValue(vValue);
			break;
		}
	}
}

//Pushes a copy of the top value on machine stack.
void copy() {
	int value = MachineStack.top().back();
	MachineStack.top().push_back(value);
}

////////////////////////////////
//////////CONTROL FLOW//////////
////////////////////////////////

//Looks for a label with the name indicated
//and if not found it creates one with the current program
//counter as the line number
void label(string label, int programCounter) {
	std::unordered_map<std::string, int>::const_iterator found;

	found = labels.find(label);

	if (found == labels.end())
		labels.insert({ label, programCounter });
}

//Jumps to the location indicated by the label.
void goTo(string label, int &programCounter) {
	std::unordered_map<std::string, int>::const_iterator found;
	
	found = labels.find(label);

	if (found != labels.end())
		programCounter = found->second;
}

//Jumps if the top value in the machine stack is 0
void goFalse(string label, int &programCounter) {
	int vValue = MachineStack.top().back();
	MachineStack.top().pop_back();
	std::unordered_map<std::string, int>::const_iterator found;

	if (vValue == 0){
		found = labels.find(label);
		if (found != labels.end())
			programCounter = found->second;
	}
}

//Jumps if the top value in the machine stack is nonzero
void goTrue(string label, int &programCounter) {
	int vValue = MachineStack.top().back();
	MachineStack.top().pop_back();
	std::unordered_map<std::string, int>::const_iterator found;

	if (vValue != 0) {
		found = labels.find(label);
		if (found != labels.end())
			programCounter = found->second;
	}
}

//stops the program execution
void halt(int &programCounter) {
	programCounter = InstructionList.size() - 1;
}

//////////////////////////////////
///////ARITHMETIC OPERATORS///////
//////////////////////////////////

//Adds top two values on the machine stack and places result beck on the stack.
void plusOp() {
	int firstV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int secondV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int plusResult = 0;

	plusResult = firstV + secondV;
	MachineStack.top().push_back(plusResult);
}

//Subtracts top two values on the mahcine stack and places result back on the stack.
void minusOp() {
	int firstV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int secondV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int minusResult = 0;

	minusResult = secondV - firstV;
	MachineStack.top().push_back(minusResult);
}

//Multiplies top two values on the machine stack and places result back on the stack.
void multiOp() {
	int firstV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int secondV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int multResult = 0;

	multResult = firstV * secondV;
	MachineStack.top().push_back(multResult);
}

//Divides the top two values on the machine stack and places result back on the stack.
void divOp() {
	int firstV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int secondV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int divResult = 0;

	divResult =  secondV / firstV;
	MachineStack.top().push_back(divResult);
}
//Mods the top two values on the machine stack and places result back on the stack.
void modOp() {
	int firstV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int secondV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int modResult = 0;

	modResult = secondV % firstV;
	MachineStack.top().push_back(modResult);
}

////////////////////////////////
///////LOGICAL OPERATORS////////
////////////////////////////////

//Logical AND the top two values on the machine stack and places result back on the stack.
void and() {
	int firstV = MachineStack.top().back();
	int secondV = MachineStack.top().back();

    if ((firstV == 1) && (secondV == 1)) {
        MachineStack.top().push_back( 1 );
    } else {
        MachineStack.top().push_back( 0 );
    }
}
//Logical NOT the top value on the machine stack and places result back on the stack.
void not() {
	int stackTop = MachineStack.top().back();
	MachineStack.top().pop_back();

	if (stackTop == 1) {
		MachineStack.top().push_back(0);
	}
	else if (stackTop == 0) {
		MachineStack.top().push_back(1);
	}
	else {
		return;
	}
}

//Logical OR the top two values on the machine stack and places result back on the stack.
void or() {
	int firstV = MachineStack.top().back();
	int secondV = MachineStack.top().back();

	if ((firstV == 0) && (secondV == 0)) {
		MachineStack.top().push_back(0);
	}
	else {
		MachineStack.top().push_back(1);
	}
}

//////////////////////////////////
///////RELATIONAL OPERATORS///////
//////////////////////////////////

//Checks if the top two values of the machine stack are different.
//Pushes 1 to the stack if the values are different, 0 otherwise
void different() {
	int firstV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int secondV = MachineStack.top().back();
	MachineStack.top().pop_back();

	if (firstV != secondV) {
		MachineStack.top().push_back(1);
	}
	else {
		MachineStack.top().push_back(0);
	}
}

//Checks if the top minus one of the machine stack is less or equal than the top
//Pushes 1 to the stack if less or equal, 0 otherwise
void lessThanEq() {
	int top = MachineStack.top().back();
	MachineStack.top().pop_back();
	int topMinusOne = MachineStack.top().back();
	MachineStack.top().pop_back();

	if (topMinusOne <= top) {
		MachineStack.top().push_back(1);
	}
	else {
		MachineStack.top().push_back(0);
	}
}

//Checks if the top minus one of the machine stack is greater or equal than the top
//Pushes 1 to the stack if greater or equal, 0 otherwise
void greaterThanEq() {
	int top = MachineStack.top().back();
	MachineStack.top().pop_back();
	int topMinusOne = MachineStack.top().back();
	MachineStack.top().pop_back();

	if (topMinusOne >= top) {
		MachineStack.top().push_back(1);
	}
	else {
		MachineStack.top().push_back(0);
	}
}

//Checks if the top minus one of the machine stack is less than the top
//Pushes 1 to the stack if less, 0 otherwise
void lessThan() {
	int top = MachineStack.top().back();
	MachineStack.top().pop_back();
	int topMinusOne = MachineStack.top().back();
	MachineStack.top().pop_back();

	if (topMinusOne < top) {
		MachineStack.top().push_back(1);
	}
	else {
		MachineStack.top().push_back(0);
	}
}

//Checks if the top minus one of the machine stack is greater than the top
//Pushes 1 to the stack if greater, 0 otherwise
void greaterThan() {
	int top = MachineStack.top().back();
	MachineStack.top().pop_back();
	int topMinusOne = MachineStack.top().back();
	MachineStack.top().pop_back();

	if (topMinusOne > top) {
		MachineStack.top().push_back(1);
	}
	else {
		MachineStack.top().push_back(0);
	}
}

//Checks if the top two values of the machine stack are equal.
//Pushes 1 to the stack if the values are equal, 0 otherwise
void equalTo() {
	int firstV = MachineStack.top().back();
	MachineStack.top().pop_back();
	int secondV = MachineStack.top().back();
	MachineStack.top().pop_back();

	if (firstV == secondV) {
		MachineStack.top().push_back(1);
	}
	else {
		MachineStack.top().push_back(0);
	}
}

////////////////////////////////
/////////////OUTPUT/////////////
////////////////////////////////


//Prints the value from the top of the machine stack.
void print() {
	int temp = MachineStack.top().back();
	OutputQueue.push_back(to_string(temp));
	OutputQueue.push_back("\n");
}

//Prints the string passed with the instruction
void show(vector<string> instruction) {
	string content;
	for (size_t i = 1; i < instruction.size(); i++) {
		content += instruction[i];
		content += " ";

	}
	OutputQueue.push_back(content);
	OutputQueue.push_back("\n");
}

////////////////////////////////
///////SUBPROGRAM CONTROL///////
////////////////////////////////


//Starts the parameter passing block.
//Increases the stack for writing variables
void begin() {
	Variables.push(*(new vector<Variable>));
	writeVariablePointer = &Variables.top();
}

//Ends parameter passing block.
//Decreases the stack for reading variables
void end() {
	Variables.pop();
	readVariablePointer = &Variables.top();
}

//Ends the function call, gets the top value from the jump stack,
//pops the machine stack and lowers the variable writing stack
void Return(int &programCounter) {
	programCounter = JumpStack.top();
	JumpStack.pop();
	MachineStack.pop();
	vector<Variable> tempV = Variables.top();
	Variables.pop();
	writeVariablePointer = &Variables.top();
	Variables.push(tempV);
	readVariablePointer = &Variables.top();
}


//Starts the function call. Sets the instruction counter
//to the location of the passed label, pushes the old instruction
//pointer value to the jump stack, pushes a new list to the
//machine stack and increases the read variable pointer
void call(string label, int &programCounter) {
	readVariablePointer = &Variables.top();
	MachineStack.push(*(new list<int>));
	JumpStack.push(programCounter);

	std::unordered_map<std::string, int>::const_iterator found;
	
	found = labels.find(label);

	if (found != labels.end())
		programCounter = found->second;
}
