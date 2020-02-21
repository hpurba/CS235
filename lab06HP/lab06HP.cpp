// lab06HP.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hikaru Purba
// CS 235	Section 004

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MyStation.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

// 1 for Console. 0 for File output
#define CONSOLE 0

using namespace std;
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
	// cout << endl;



	//BEGINNING OF PROGRAM
	MyStation<unsigned int> myStation;

	//BEGIN OF PROGRAM
	string command;
	string line;
	while (getline(in, line))
	{
		if (line.size() == 0) continue; // Empty line, continue
		istringstream iss(line);
		getline(iss, command, ':');
		out << line << " ";
		string expression;
		unsigned int carNumber = 0;

		// Add:Station, Add:Queue, Add:Stack
		if (command == "Add")
		{
			getline(iss, command, ' ');
			if (command == "station")
			{
				getline(iss, expression, ' ');
				carNumber = stoi(expression);
				out << myStation.addCar(carNumber) << endl;
			}
			else if (command == "queue")
			{
				out << myStation.addQueue() << endl;
			}
			else
			{
				out << myStation.addStack() << endl;
			}
		}

		// Remove:Station, Remove:Queue, Remove:Stack
		else if (command == "Remove")
		{
			getline(iss, command);
			if (command == "station")
			{
				out << myStation.removeCar() << endl;
			}
			else if (command == "queue")
			{
				out << myStation.removeQueue() << endl;
			}
			else
			{
				out << myStation.removeStack() << endl;
			}
		}

		// Top:Station, Top:Queue, Top:Stack
		else if (command == "Top")
		{
			getline(iss, command);
			if (command == "station")
			{
				getline(iss, expression);
				carNumber = stoi(expression);
				out << myStation.topCar() << endl;
			}
			else if (command == "queue")
			{
				out << myStation.topQueue() << endl;
			}
			else
			{
				out << myStation.topStack() << endl;
			}
		}

		// Size:Stack, Size:Queue
		else if (command == "Size")
		{
			getline(iss, command);
			if (command == "queue")
			{
				out << myStation.sizeQueue() << endl;
			}
			else
			{
				out << myStation.sizeStack() << endl;
			}
		}

		// FIND
		else if (command == "Find")
		{
			getline(iss, expression);
			carNumber = stoi(expression);
			out << myStation.find(carNumber) << endl;
		}
		
		// TRAIN
		else if (command == "Train")
		{
			out << myStation.toString() << endl;
		}

		// Invalid input
		else
		{
			out << "Error, command not found" << endl;
		}
	}


	// Print out to console or 
	if (!CONSOLE)		
	{
		ofstream * pout = (ofstream *)&out;
		pout->close();							
		delete pout;
	}
}