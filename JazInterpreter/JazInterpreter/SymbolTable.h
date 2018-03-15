#pragma once
////////////////////////////////////////////////////////////////
//	Description:This file contains the global variables to be
//	used by the interpreter for holding the instruction, the
//	variables and the output information
////////////////////////////////////////////////////////////////

#include "Variable.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <unordered_map>
using namespace std;

//Holds the labels contained in the program
extern unordered_map<string, int> labels;

//Stack of jumps performed during the program execution
extern stack<int> JumpStack;

//Holds the instructions of the program to be run in order
extern vector<vector<string>> InstructionList;

//Holds the information to be written into the output files
extern list<string> OutputQueue;

//This is the stack that the Jaz machine uses for performing its operations
extern stack<list<int>> MachineStack;

//List of variables contained in the program
extern stack<vector<Variable>> Variables;

//Pointer to the list of variables on the current scope for writing
extern vector<Variable> *writeVariablePointer;

//Pointer to the list of variables on the current scope for reading
extern vector<Variable> *readVariablePointer;

//Initializes the variable and machine stacks
void initializeSymbols();