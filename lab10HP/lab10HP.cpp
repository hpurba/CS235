// lab10HP.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hikaru Purba
// CS 235	Section 004

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "QSInterface.h"
#include "QS.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

// 0 file, 1 console
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
	cout << "input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << endl << "output file: " << (CONSOLE ? "cout" : argv[2]);

	//assign output to either console or file
	ostream& out = CONSOLE ? cout : *(new ofstream(argv[2]));
	cout << endl;





	// Variables
	string command;
	QuickSort<int> myQS; 
	

	for (string line; getline(in, line);)
	{
		if (line != "")
		{
			out << line; // output stream the whole line.
			istringstream iss(line); 
			iss >> command;

			// Make the Array 
			if (command == "QuickSort")
			{
				string size;
				iss >> size;
				size_t myArraySize = stoi(size); // myArraySize holds the size of the newly created array. size_t? or int?
				bool completed;
				completed = myQS.createArray(myArraySize);

				if (completed)
				{
					out << " OK\n";
				}
				else
				{
					out << " Error\n";
				}

			}

			// Capacity of Array
			else if (command == "Capacity")
			{
				int capacity = myQS.capacity();
				out << " " << capacity << "\n";
			}

			// Clear the Array
			else if (command == "Clear")
			{
				bool completed;
				completed = myQS.clear();
				if (completed) {
					out << " OK\n";
				}
				else {
				}
			}

			// Add stuff to the array
			else if (command == "AddToArray")
			{
				/*
				for (size_t i = 0; i < myQS.getsize(); i++) {
					string element;
					iss >> element;
					
					if (myQS.addElement(stoi(element))) {
						out << " OK\n";
					}
					else {
						// try again.
					}
				}
				*/
				
			}
			else if (command == "Size") {
				// returns the number of elements currently in the array.
				out << " => returns the number of elements currently in the array\n";
			}
			else
			{
				// no code here yet.
			}
		}
	}


	/*


	// Variables
	string command; 
	string arraySize;

	for (string line; getline(in, line);)
	{
		if (line != "")
		{
			out << line;
			istringstream iss(line);
			iss >> command;

			if (command == "QuickSort")
			{
				stringstream out;
				iss >> arraySize;
				int capacity = std::stoi(arraySize);
				// int myArray[capacity];
				out << arraySize << capacity << "OK" << "\n";

			}
			else if (command == "Add to Array")
			{
				stringstream out;
				// Add the entries to the array
				out << "Add to Array command" << "\n";
			}
			else
			{
				stringstream out;
				out << "else" << "\n";
				//
			}
		}
	}
	*/

	// myArray.Free();
	if (!CONSOLE)
	{
		ofstream * pout = (ofstream *)&out;
		pout->close();
		delete pout;
	}
}