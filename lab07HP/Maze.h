#ifndef MAZE_H
#define MAZE_H
#include "MazeInterface.h"
#include <string>

using namespace std;
class Maze :public MazeInterface
{
private:
	int HEIGHT;
	int WIDTH;
	int LAYER;
	int ***myArray;
	enum CellValue { OPEN, BLOCKED, PATH, EXIT, TEMPORARY, cLEFT, cRIGHT, cUP, cDOWN, cOUT, cIN };
	enum MoveDirection { LEFT, RIGHT, UP, DOWN, OUT, IN };
public:
	Maze() :HEIGHT(0), WIDTH(0), LAYER(0) {};
	Maze(int height, int width, int layer);
	~Maze();
	void setValue(int height, int width, int layer, int value);

	/** Solve maze
	   @return true if solveable, else false
	*/
	bool find_maze_path();
	bool find_maze_path(int height, int width, int layer, MoveDirection dir, string& path);
	void maze_path_bonus(string& path);
	void append_path_coordinate(int height, int width, int layer, string& path);
	/** Output maze (same order as input maze)
	  @return string of 2D layers
	*/
	string toString() const;
};


// Construct Maze Array
Maze::Maze(int height, int width, int layer)
{
	HEIGHT = height;
	WIDTH = width;
	LAYER = layer;
	myArray = new int**[HEIGHT];
	for (int j = 0; j < HEIGHT; j++)
	{
		myArray[j] = new int*[WIDTH];
		for (int k = 0; k < WIDTH; k++)
		{
			myArray[j][k] = new int[LAYER];
		}
	}
}

// Destruct Maze Array
Maze::~Maze()
{
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int k = 0; k < WIDTH; k++)
			delete[] myArray[j][k];
		delete[] myArray[j];
	}
	delete[] myArray;
}

void Maze::setValue(int height, int width, int layer, int value)
{
	myArray[height][width][layer] = value;
}

void Maze::maze_path_bonus(string& path)
{
	stringstream ss(path);
	string line;
	getline(ss, line);
	string sTemp;
	int startHeight, startWidth, startLayer;
	stringstream ssExpression(line);
	getline(ssExpression, sTemp, ',');
	startHeight = stoi(sTemp);
	getline(ssExpression, sTemp, ',');
	startWidth = stoi(sTemp);
	getline(ssExpression, sTemp, ',');
	startLayer = stoi(sTemp);

	while (getline(ss, line))
	{

		int endHeight, endWidth, endLayer;
		CellValue cellDirection;
		stringstream ssExpression2(line);
		getline(ssExpression2, sTemp, ',');
		endHeight = stoi(sTemp);
		getline(ssExpression2, sTemp, ',');
		endWidth = stoi(sTemp);
		getline(ssExpression2, sTemp, ',');
		endLayer = stoi(sTemp);

		//Determine direction
		if (startHeight == endHeight)
		{
			if (startWidth == endWidth)
			{
				if (startLayer > endLayer)
					cellDirection = cOUT;
				else
					cellDirection = cIN;
			}
			else
			{
				if (startWidth > endWidth)
					cellDirection = cLEFT;
				else
					cellDirection = cRIGHT;
			}
		}
		else
		{
			if (startHeight > endHeight)
				cellDirection = cUP;
			else
				cellDirection = cDOWN;
		}
		myArray[startHeight][startWidth][startLayer] = cellDirection;
		startHeight = endHeight;
		startWidth = endWidth;
		startLayer = endLayer;
	}
}

void Maze::append_path_coordinate(int height, int width, int layer, string& path)
{
	ostringstream os;
	stringstream in;
	in << height << "," << width << "," << layer << endl << path;
	in >> os.rdbuf();
	path = os.str();
}

bool Maze::find_maze_path()
{
	string ss;
	bool bFound = find_maze_path(0, 0, 0, IN, ss);
	if (ss != "")
		maze_path_bonus(ss);
	return bFound;
}

//The MoveDirection is needed for efficiency.  Without it, the recursion would go back to the same cell and try to
//traverse the path again.
bool Maze::find_maze_path(int height, int width, int layer, MoveDirection dir, string& path)
{
	bool bFound = false;

	//Check boundary
	if ((height < 0) || (height >= HEIGHT) || (width < 0) || (width >= WIDTH) || (layer < 0) || (layer >= LAYER))
		return false;
	if (myArray[height][width][layer] != OPEN)
		return false;
	if ((height == (HEIGHT - 1)) && (width == (WIDTH - 1)) && (layer == (LAYER - 1)))
	{
		append_path_coordinate(height, width, layer, path);
		myArray[height][width][layer] = EXIT;
		return true;
	}

	myArray[height][width][layer] = PATH;

	if (dir == LEFT || dir == UP || dir == DOWN || dir == OUT || dir == IN)
		bFound = find_maze_path(height, width - 1, layer, LEFT, path);
	if (!bFound && (dir == RIGHT || dir == UP || dir == DOWN || dir == OUT || dir == IN))
		bFound = find_maze_path(height, width + 1, layer, RIGHT, path);
	if (!bFound && (dir == LEFT || dir == RIGHT || dir == UP || dir == OUT || dir == IN))
		bFound = find_maze_path(height - 1, width, layer, UP, path);
	if (!bFound && (dir == LEFT || dir == RIGHT || dir == DOWN || dir == OUT || dir == IN))
		bFound = find_maze_path(height + 1, width, layer, DOWN, path);
	if (!bFound && (dir == LEFT || dir == RIGHT || dir == UP || dir == DOWN || dir == OUT))
		bFound = find_maze_path(height, width, layer - 1, OUT, path);
	if (!bFound && (dir == LEFT || dir == RIGHT || dir == UP || dir == DOWN || dir == IN))
		bFound = find_maze_path(height, width, layer + 1, IN, path);
	if (bFound)
	{

		append_path_coordinate(height, width, layer, path);
		return true;
	}

	myArray[height][width][layer] = TEMPORARY;
	return false;
}

string Maze::toString() const
{
	stringstream out;
	for (int i = 0; i < LAYER; i++)
	{
		out << "Layer " << (i + 1) << endl;
		for (int j = 0; j < HEIGHT; j++)
		{
			for (int k = 0; k < WIDTH; k++)
			{
				int nValue = myArray[j][k][i];

				switch (nValue)
				{
				case TEMPORARY: case OPEN:			out << "_" << " ";			break;
				case BLOCKED:						out << "X" << " ";			break;
				case cRIGHT:						out << "R" << " ";			break;
				case cLEFT:							out << "L" << " ";			break;
				case cUP:							out << "U" << " ";			break;
				case cDOWN:							out << "D" << " ";			break;
				case cIN:							out << "I" << " ";			break;
				case cOUT:							out << "O" << " ";			break;
				case EXIT:							out << "E" << " ";			break;
				default:							out << nValue << " ";		break;
				}
			}
			out << endl;
		}
	}
	return out.str();
}

#endif // MAZE_INTERFACE_H
