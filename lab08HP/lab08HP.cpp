// lab08HP.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hikaru Purba
// CS 235	Section 004


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BST.h"


#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

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


	string command;
	string expression;
	BST<int> myBSTInt;
	BST<string>myBSTStr;
	bool intMode = false;
	bool bStatus = false;

	for (string line; getline(in, line);)
	{
		out << line << " ";
		istringstream iss(line);
		iss >> command;
		if (command == "INT")
		{
			intMode = true;
			out << "true" << endl;

		}
		else if (command == "STRING")
		{
			intMode = false;
			out << "true" << endl;
		}
		else if (command == "add")
		{
			iss >> expression;
			if (intMode)
				bStatus = myBSTInt.addNode(stoi(expression));
			else
				bStatus = myBSTStr.addNode(expression);
			if (bStatus)
				out << "true" << endl;
			else
				out << "false" << endl;
		}
		else if (command == "print")
		{
			if (intMode)
				out << ": " << myBSTInt.toString() << endl;
			else
				out << ": " << myBSTStr.toString() << endl;
		}
		else if (command == "clear")
		{
			if (intMode)
				bStatus = myBSTInt.clearTree();
			else
				bStatus = myBSTStr.clearTree();
			if (bStatus)
				out << "true" << endl;
			else
				out << "false" << endl;
		}
		else if (command == "size")
		{
			if (intMode)
				out << myBSTInt.size() << endl;
			else
				out << myBSTStr.size() << endl;
		}
		else if (command == "remove")
		{
			iss >> expression;
			if (intMode)
				bStatus = myBSTInt.removeNode(stoi(expression));
			else
				bStatus = myBSTStr.removeNode(expression);
			if (bStatus)
				out << "true" << endl;
			else
				out << "false" << endl;
		}
		else if (command == "find")
		{
			iss >> expression;
			if (intMode)
			{
				int tempInt = stoi(expression);
				BST<int>::Iterator iter = myBSTInt.Find(tempInt);
				BST<int>::Iterator iterend = myBSTInt.end();
				if (!(iter != iterend))
					out << "not found" << endl;
				else
					out << "found" << endl;
			}
			else
			{
				BST<string>::Iterator iter = myBSTStr.Find(expression);
				BST<string>::Iterator iterend = myBSTStr.end();
				if (!(iter != iterend))
					out << "not found" << endl;
				else
					out << "found" << endl;
			}

		}
		else if (command == "tree")
		{
			if (intMode)
			{
				BST<int>::Iterator iter = myBSTInt.begin();
				BST<int>::Iterator iterend = myBSTInt.end();
				out << ":";
				if (!(iter != iterend))
					out << " empty";
				else
					for (; iter != iterend; iter++)
						out << *iter << " ";
				out << endl;
			}
			else
			{
				BST<string>::Iterator iter = myBSTStr.begin();
				BST<string>::Iterator iterend = myBSTStr.end();
				out << ":";
				if (!(iter != iterend))
					out << "empty";
				else
					for (; iter != iterend; iter++)
						out << *iter << " ";
				out << endl;
			}
		}
	}

	if (!CONSOLE)
	{
		ofstream * pout = (ofstream *)&out;
		pout->close();
		delete pout;
	}
}

