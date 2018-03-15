////////////////////////////////////////////////////////////////
//	Description:This file contains the input/output module of
//	the interpreter. It is in charge of reading a program to be
//	interpreted and saving each of its instructions. It also
//	write the results of running the program into an indicated
//	output file
////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "FileManipulation.h"
#include "SymbolTable.h"
using namespace std;

//Extract each line of the file indicated by filename and
//write each line as an entry in the vector instructions
bool ReadFile(string fileName, vector<string> &instructions){
	ifstream inputFile;
	string line;
	bool read = false;

	//check if file has.jaz at the end
	size_t found = fileName.find(".jaz");

	if (found==string::npos)
		fileName.append(".jaz");

	inputFile.open(fileName);

	if (inputFile.good()){
		string line;
		while (!inputFile.eof()) {
			getline(inputFile, line);
			//Ignore empty lines
			if (line != "")
				instructions.push_back(line);
		}
		read = true;
	}
	else
		cout << "Could not read input file." << endl;

	inputFile.close();

	return read;
}

//Write the contents of the Output queue to the file indicated in filename
void WriteFile(string fileName) {
	ofstream outputFile;

	//check if file has.jaz at the end
	size_t found = fileName.find(".jaz");
	//remove it if necessary
	if (found != string::npos)
		for (int i = 0; i < 4; i++)
			fileName.pop_back();

	fileName.append(".out");
	outputFile.open(fileName);
	if (outputFile.good()) {
		while(!OutputQueue.empty()) {
			outputFile << OutputQueue.front();
			OutputQueue.pop_front();
		}
		cout << "Successful operation of interpreter. Check results in " << fileName << endl;
	}
	else
		cout << "Could not write to output file." << endl;

	outputFile.close();
}
