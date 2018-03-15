////////////////////////////////////////////////////////////////
//	Description:This file contains the main entry to the
//				interpreter application. It calls fucntions in
//				the different modules in order to get
//				the information from an source file, extract
//				the instructions from it, execute them and then
//				write the results to another file
////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>

#include "FileManipulation.h"
#include "ControlManipulation.h"

using namespace std;

int main(int argc, char* argv[])
{
	//Check for input parameters
	if (argv[1] != nullptr)
	{
		string file = argv[1];	
		vector<string> instructions;

		bool read = ReadFile(file, instructions);
		if (read) {
			separateInstructions(instructions);
			extractLabels();
			runProgram();
			WriteFile(file);
		}
	}
	else
		cout << "Error running the interpreter. You need to provide a source file." << endl;
	return 0;
}