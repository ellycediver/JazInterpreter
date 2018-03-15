#pragma once
////////////////////////////////////////////////////////////////
//	Description:This file contains the module of the interpreter
//	that runs the program and calls for the execution of each
//	individual instruction. It is also in charge of separating
//	the information obtained from the file into instructions
//	usable by the interpreter
////////////////////////////////////////////////////////////////
#include <vector>
#include <string>
using namespace std;

//Global counter of the instruction being executed
static int programCounter = 0;

//Separates the lines read from the program file into
//operators and operands
void separateInstructions(vector<string> instructions);

//Finds all the labels in the program and saves their line number
void extractLabels();

//Iterates through the list of instructions and calls for the execution
//of each individual instruction
void runProgram();

//Calls for the execution of the proper instruction according to the operator
void executeInstruction(vector<string> instruction);
