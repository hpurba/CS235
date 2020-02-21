// lab07HP.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hikaru Purba
// CS 235	Section 004

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Maze.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

// 1 for Console. 0 for File output
#define CONSOLE 1

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

	//assign output to either console or file
	ostream& out = CONSOLE ? cout : *(new ofstream(argv[2]));


	//BEGINNING OF PROGRAM
	string line, height, width, layer;
	int nHeight, nWidth, nLayer;
	getline(in, line);
	istringstream iss(line);
	getline(iss, height, ' ');
	getline(iss, width, ' ');
	getline(iss, layer, ' ');
	nHeight = stoi(height);
	nWidth = stoi(width);
	nLayer = stoi(layer);
	Maze myMaze(nHeight, nWidth, nLayer);

	// Set values in maze
	for (int i = 0; i < nLayer; i++)
	{
		//Throw away
		getline(in, line);
		//For each row
		for (int j = 0; j < nHeight; j++)
		{
			getline(in, line);
			istringstream issRow(line);
			string expression;
			for (int k = 0; k < nWidth; k++)
			{
				getline(issRow, expression, ' ');
				myMaze.setValue(j, k, i, stoi(expression));
			}

		}
	}

	/*
	RESULT
	*/
	out << "Solve Maze: " << endl;
	out << myMaze.toString();
	if (myMaze.find_maze_path())
	{
		out << endl << "Solution: " << endl;
		out << myMaze.toString();
	}
	else
		out << endl << "No Solution Exists!" << endl;


	if (!CONSOLE)
	{
		ofstream * pout = (ofstream *)&out;
		pout->close();
		delete pout;
	}
}