#pragma once
////////////////////////////////////////////////////////////////
//	Description:This file contains the input/output module of
//	the interpreter. It is in charge of reading a program to be
//	interpreted and saving each of its instructions. It also
//	write the results of running the program into an indicated
//	output file
////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
using namespace std;

//Extract each line of the file indicated by filename and
//write each line as an entry in the vector instructions
bool ReadFile(string fileName, vector<string> &instructions);

//Write the contents of the Output queue to the file indicated in filename
void WriteFile(string fileName);
