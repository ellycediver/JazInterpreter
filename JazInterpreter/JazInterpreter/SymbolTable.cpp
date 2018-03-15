#include "SymbolTable.h"
////////////////////////////////////////////////////////////////
//	Description:This file contains the global variables to be
//	used by the interpreter for holding the instruction, the
//	variables and the output information
////////////////////////////////////////////////////////////////

//Holds the labels contained in the program
unordered_map<string, int> labels;

//Stack of jumps performed during the program execution
stack<int> JumpStack;

//Holds the instructions of the program to be run in order
vector<vector<string>> InstructionList;

//Holds the information to be written into the output files
list<string> OutputQueue;

//This is the stack that the Jaz machine uses for performing its operations
stack<list<int>> MachineStack;

//List of variables contained in the program
stack<vector<Variable>> Variables;

//Pointer to the list of variables on the current scope for writing
vector<Variable> *writeVariablePointer;

//Pointer to the list of variables on the current scope for reading
vector<Variable> *readVariablePointer;

//Initializes the variable and machine stacks
void initializeSymbols() {
	Variables.push(*(new vector<Variable>));
	MachineStack.push(*(new list<int>));
	writeVariablePointer = &Variables.top();
	readVariablePointer = &Variables.top();
}