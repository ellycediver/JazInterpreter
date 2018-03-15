#pragma once
////////////////////////////////////////////////////////////////
//	Description:This file contains the implementation of the
//	functions performed by the jaz machine
////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>
using namespace std;

////////////////////////////////
///////STACK MANIPULATION///////
////////////////////////////////

//Pushes value to stack
void push(string value);

//Pushes the value of the passed variable on the machine stack.
//Searches for the variable in the list of variables within the scope and
//if found pushes its value into the machine stack
void rvalue(string variable);

//Pushes the address of the variable indicated into the machine stack.
//Searches for the variable in the list of variables available in the
//scope and pushes it if found, or it creates a new variable if not
void lvalue(string variable);

//Pops the top value of the stack
void pop();

//Takes the value on top of the stack and places it into the location placed below it.
//It also pops both values from the stack
void colEquals();

//Pushes a copy of the top value on machine stack.
void copy();

////////////////////////////////
//////////CONTROL FLOW//////////
////////////////////////////////

//Looks for a label with the name indicated
//and if not found it creates one with the current program
//counter as the line number
void label(string label, int programCounter);

//Jumps to the location indicated by the label.
void goTo(string label, int &programCounter);

//Jumps if the top value in the machine stack is 0
void goFalse(string label, int &programCounter);

//Jumps if the top value in the machine stack is nonzero
void goTrue(string label, int &programCounter);

//stops the program execution
void halt(int &programCounter);

//////////////////////////////////
///////ARITHMETIC OPERATORS///////
//////////////////////////////////

//Adds top two values on the machine stack and places result beck on the stack.
void plusOp();

//Subtracts top two values on the mahcine stack and places result back on the stack.
void minusOp();

//Multiplies top two values on the machine stack and places result back on the stack.
void multiOp();

//Divides the top two values on the machine stack and places result back on the stack.
void divOp();

//Mods the top two values on the machine stack and places result back on the stack.
void modOp();

////////////////////////////////
///////LOGICAL OPERATORS////////
////////////////////////////////

//Logical AND the top two values on the machine stack and places result back on the stack.
void and();

//Logical NOT the top value on the machine stack and places result back on the stack.
void not();

//Logical OR the top two values on the machine stack and places result back on the stack.
void or ();

//////////////////////////////////
///////RELATIONAL OPERATORS///////
//////////////////////////////////

//Checks if the top to values of the machine stack are different.
//Pushes 1 to the stack if the values are different, 0 otherwise
void different();

//Checks if the top minus one of the machine stack is less or equal than the top
//Pushes 1 to the stack if less or equal, 0 otherwise
void lessThanEq();

//Checks if the top minus one of the machine stack is greater or equal than the top
//Pushes 1 to the stack if greater or equal, 0 otherwise
void greaterThanEq();

//Checks if the top minus one of the machine stack is less than the top
//Pushes 1 to the stack if less, 0 otherwise
void lessThan();

//Checks if the top minus one of the machine stack is greater than the top
//Pushes 1 to the stack if greater, 0 otherwise
void greaterThan();

//Checks if the top two values of the machine stack are equal.
//Pushes 1 to the stack if the values are equal, 0 otherwise
void equalTo();

////////////////////////////////
/////////////OUTPUT/////////////
////////////////////////////////

//Prints the value from the top of the machine stack.
void print();

//Prints the string passed with the instruction
void show(vector<string>);

////////////////////////////////
///////SUBPROGRAM CONTROL///////
////////////////////////////////

//Starts the parameter passing block.
//Increases the stack for writing variables
void begin();

//Ends parameter passing block.
//Decreases the stack for reading variables
void end();

//Ends the function call, gets the top value from the jump stack,
//pops the machine stack and lowers the variable writing stack
void Return(int &programCounter);

//Starts the function call. Sets the instruction counter
//to the location of the passed label, pushes the old instruction
//pointer value to the jump stack, pushes a new list to the
//machine stack and increases the read variable pointer
void call(string label, int &programCounter);