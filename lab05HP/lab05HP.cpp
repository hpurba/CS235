// lab05HP.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hikaru Purba
// CS 235	Section 004

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include "ExpressionManagerInterface.h"
#include "ExpressionManager.h"


// Memory Checking
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

// Output 1 to console, 0 to file
#define CONSOLE 1

using namespace std;

// MAIN
int main(int argc, char* argv[])
{
	VS_MEM_CHECK               // enable memory leak check

		if (argc < 3)
		{
			cerr << "please provide name of input and output files";
			return 1;
		}
	// cout << "input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "unable to open " << argv[1] << " for input";
		return 2;
	}
	// cout << endl << "output file: " << (CONSOLE ? "cout" : argv[2]);

	//assign output to either console or file
	ostream& out = CONSOLE ? cout : *(new ofstream(argv[2]));



	string line;
	string command;
	ExpressionManager expMan;
	// ExpressionManager expManager;
	while (getline(in, line))
	{
		//Try Catch for error
		try
		{
			istringstream iss(line);
			iss >> command;
			if (line.size() == 0) continue;		// Blank line, continue
			if (command == "Expression:")
			{
				// If command is the expression
				string expression;
				getline(iss, expression);
				out << "Expression: " << expression << endl;
				expMan.initialize(expression);		// Getting the actual expression
				continue;
			}
			else if (command == "Infix:")
			{
				// If command is the Infix
			}
			else if (command == "Postfix:")
			{
				// If command is the Postfix
			}
			else if (command == "Prefix:")
			{
				// If the command is Prefix
			}
			else if (command == "Value:")
			{
				// If the command is Value
			}
			else
			{
				throw "command not found";
				break;
			}
		}

		// Catch
		catch (const std::exception&)
		{
			out << "Here is where I put why the expression was invalid" << endl;
		}
	}



	// OUTPUT
	if (!CONSOLE)
	{
		ofstream * pout = (ofstream *)&out;
		pout->close();
		delete pout;
	}
};

