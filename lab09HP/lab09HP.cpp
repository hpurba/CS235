// lab09HP.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hikaru Purba
// CS 235	Section 004

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Map.h"

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
	string value;
	Map<string, string> Pokemon;
	Map<string, string> Moves;
	Map<string, Set<string>> Effectives;
	Map<string, Set<string>> Ineffectives;
	bool intMode = false;
	bool bStatus = false;

	for (string line; getline(in, line);)
	{
		if (line != "")
		{
			out << line;
			istringstream iss(line);

			iss >> command;
			if (command == "Set:")
			{
				Set<string> mySet;
				while (iss >> expression)
				{
					mySet.insert(expression);
				};
				out << endl << "  [" << mySet.toString() << "]" << endl;
			}
			else if (command == "Pokemon:")
			{
				iss >> expression;
				iss >> value;

				Pokemon[expression] = value;
				Pokemon.reallocate();
				out << endl;
			}
			else if (command == "Move:")
			{
				iss >> expression;
				iss >> value;
				Moves[expression] = value;
				Moves.reallocate();
				out << endl;
			}
			else if (command == "Pokemon")
			{
				out << ": " << Pokemon.size() << "/" << Pokemon.max_size() << endl;
				out << Pokemon.toString();
				out << endl;
			}
			else if (command == "Moves")
			{
				out << ": " << Moves.size() << "/" << Moves.max_size() << endl;
				out << Moves.toString();
				out << endl;
			}
			else if (command == "Effective:")
			{
				iss >> expression;
				if (Effectives[expression].size() == 0)
				{
					Effectives[expression] = Set<string>();
					while (iss >> value)
					{
						Effectives[expression].insert(value);
					};
					Effectives.reallocate();
				}
				out << endl;
			}
			else if (command == "Ineffective:")
			{
				iss >> expression;
				if (Ineffectives[expression].size() == 0)
				{
					Ineffectives[expression] = Set<string>();
					while (iss >> value)
					{
						Ineffectives[expression].insert(value);
					};
					Ineffectives.reallocate();
				}
				out << endl;
			}
			else if (command == "Effectivities")
			{
				out << ": " << Effectives.size() << "/" << Effectives.max_size() << endl;
				out << Effectives.toString();
				out << endl;
			}
			else if (command == "Ineffectivities")
			{
				out << ": " << Ineffectives.size() << "/" << Ineffectives.max_size() << endl;
				out << Ineffectives.toString();
				out << endl;
			}
			else if (command == "Battle:")
			{
				out << endl;
				string Pokemon01;
				string Pokemon02;
				string Pokemon01Move;
				string Pokemon02Move;
				int damage1To2 = 0;
				int damage2To1 = 0;

				iss >> Pokemon01;
				iss >> Pokemon01Move;
				iss >> Pokemon02;
				iss >> Pokemon02Move;
				size_t Pokemon01EffectiveCount = Effectives[Moves[Pokemon01Move]].count(Pokemon[Pokemon02]);
				size_t Pokemon01IneffectiveCount = Ineffectives[Moves[Pokemon01Move]].count(Pokemon[Pokemon02]);
				size_t Pokemon02EffectiveCount = Effectives[Moves[Pokemon02Move]].count(Pokemon[Pokemon01]);
				size_t Pokemon02IneffectiveCount = Ineffectives[Moves[Pokemon02Move]].count(Pokemon[Pokemon01]);



				out << "  " << Pokemon01 << " (" << Pokemon01Move << ") vs " << Pokemon02 << " (" << Pokemon02Move << ")" << endl;
				out << "  " << Pokemon01 << " is a " << Pokemon[Pokemon01] << " type Pokemon" << endl;
				out << "  " << Pokemon02 << " is a " << Pokemon[Pokemon02] << " type Pokemon" << endl;
				out << "  " << Pokemon01Move << " is a " << Moves[Pokemon01Move] << " type move" << endl;
				out << "  " << Pokemon02Move << " is a " << Moves[Pokemon02Move] << " type move" << endl;

				out << "  " << Pokemon01Move << " is super effective against [" << Effectives[Moves[Pokemon01Move]].toString() << "] type Pokemon" << endl;
				out << "  " << Pokemon01Move << " is ineffective against [" << Ineffectives[Moves[Pokemon01Move]].toString() << "] type Pokemon" << endl;
				if (Pokemon01EffectiveCount == Pokemon01IneffectiveCount)
				{
					damage1To2 = 0;
					out << "  " << Pokemon01 << "' " << Pokemon01Move << " is effective against " << Pokemon02 << endl;
				}
				else if (Pokemon01EffectiveCount > Pokemon01IneffectiveCount)
				{
					damage1To2 = 1;
					out << "  " << Pokemon01 << "' " << Pokemon01Move << " is super effective against " << Pokemon02 << endl;
				}
				else
				{
					damage1To2 = -1;
					out << "  " << Pokemon01 << "' " << Pokemon01Move << " is ineffective against " << Pokemon02 << endl;
				}

				out << "  " << Pokemon02Move << " is super effective against [" << Effectives[Moves[Pokemon02Move]].toString() << "] type Pokemon" << endl;
				out << "  " << Pokemon02Move << " is ineffective against [" << Ineffectives[Moves[Pokemon02Move]].toString() << "] type Pokemon" << endl;
				if (Pokemon02EffectiveCount == Pokemon02IneffectiveCount)
				{
					damage2To1 = 0;
					out << "  " << Pokemon02 << "' " << Pokemon02Move << " is effective against " << Pokemon01 << endl;
				}
				else if (Pokemon02EffectiveCount > Pokemon02IneffectiveCount)
				{
					damage2To1 = 1;
					out << "  " << Pokemon02 << "' " << Pokemon02Move << " is super effective against " << Pokemon01 << endl;
				}
				else
				{
					damage2To1 = -1;
					out << "  " << Pokemon02 << "' " << Pokemon02Move << " is ineffective against " << Pokemon01 << endl;
				}


				if ((damage1To2 - damage2To1) > 0)
				{
					out << "  " << "In the battle between " << Pokemon01 << " and " << Pokemon02 << ", " << Pokemon01 << " wins!" << endl;
				}
				else if ((damage1To2 - damage2To1) < 0)
				{
					out << "  " << "In the battle between " << Pokemon01 << " and " << Pokemon02 << ", " << Pokemon02 << " wins!" << endl;
				}
				else
				{
					out << "  " << "The battle between " << Pokemon01 << " and " << Pokemon02 << " is a tie" << endl;
				}

				out << endl;
			}

		}
		else
			out << endl;
	}



	if (!CONSOLE)
	{
		ofstream * pout = (ofstream *)&out;
		pout->close();
		delete pout;
	}
}

