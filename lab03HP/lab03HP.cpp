// Lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hikaru Purba
// CS 235	Section 004

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

// Output 1 to console, 0 to file
#define CONSOLE 0
#define ARRAY_SIZE 1000

using namespace std;

/************************************/
//TEMPLATE CLASS
/***********************************/
template<typename T>
class MyArray
{
private:
	size_t size_;
	T* array_;
public:
	MyArray(size_t maxSize) : size_(0)
	{
		array_ = (T*)malloc(maxSize * sizeof(T));
	};
	void push_back(T item) { array_[size_++] = item; };
	void Free() { free(array_); };
	string toString();

	class Iterator
	{
	private:
		size_t index_;
		T* array_;
		size_t sizeofarray_;
	public:
		Iterator(T* a, size_t index, size_t sizearray) : array_(a), index_(index), sizeofarray_(sizearray) {};
		T& operator[](size_t i) const { return array_[i]; };
		T& operator*() const { return array_[index_]; };
		Iterator operator++()
		{
			index_ = index_ + 1;
			return MyArray<T>::Iterator(array_, index_, sizeofarray_);
		};
		bool operator!=(MyArray<T>::Iterator& righthandside) {

			return *righthandside != array_[index_];
		};
		bool operator==(const T& righthandside) {
			return righthandside == array_[index_];
		};
		string toString();
		friend std::ostream& operator<< (ostream& os, Iterator ownIterator) {
			os << ownIterator.toString();
			return os;
		};
	};
	Iterator begin() { return MyArray<T>::Iterator(array_, 0, size_); };
	Iterator end() { return MyArray<T>::Iterator(array_, size_, size_); };
	friend std::ostream& operator<< (ostream& os, MyArray ownArray) {
		os << ownArray.toString();
		return os;
	};
};

template<typename T>
string MyArray<T>::toString()
{
	stringstream out;

	for (size_t i = 0; i < size_; i++)
	{
		if (i != 0 && i % 10 == 0)
			out << endl;
		out << array_[i];
		if (i < size_ - 1)
			out << " ";
	}
	return out.str();
}

template<typename T>
string MyArray<T>::Iterator::toString()
{
	stringstream out;
	out << "size=" << sizeofarray_ << " index=" << index_;
	return out.str();
}

/****** END OF CLASSES ******/


/****** START OF METHODS ****/

bool isPrime(int number)
{
	int i;
	if (number < 2) return false;
	for (i = 2; i < number; ++i)
	{
		if (number % i == 0) return false;
	}
	return true;
}

template<typename T>
string printMyArray(MyArray<T>& myArray)
{
	stringstream out;
	//Print my Array
	out << "myArray: " << endl;
	out << myArray;
	out << endl << endl;
	return out.str();
}

template<typename T>
string printIterator(MyArray<T>& myArray)
{
	stringstream out;
	out << "ITERATORS: " << endl;
	out << "begin(): " << myArray.begin() << endl;
	out << "end(): " << myArray.end() << endl;
	out << endl;
	return out.str();
}

template<typename T>
string printSequential(MyArray<T>& myArray)
{
	stringstream out;
	MyArray<int>::Iterator iter = myArray.begin();
	MyArray<int>::Iterator iterend = myArray.end();
	out << "SEQUENTIAL:" << endl;
	for (int i = 0; iter != iterend; ++iter)
	{
		if (i != 0 && i % 10 == 0)
			out << endl;
		out << *iter << " ";
		i++;
	}
	out << endl << endl;
	return out.str();
}

template<typename T>
string printPrime(MyArray<T>& myArray)
{
	stringstream out;
	unsigned int count = 0;
	out << "PRIME: " << endl;
	MyArray<int>::Iterator iter = myArray.begin();
	MyArray<int>::Iterator iterend = myArray.end();
	for (int i = 0; iter != iterend; ++iter)
	{
		if (count != 0 && count % 10 == 0)
		{
			out << endl;
			count = 0;
		}
		if (isPrime(*iter))
		{
			out << *iter << " ";
			count++;
		}
	}
	out << endl << endl;
	return out.str();
}

template<typename T>
string printComposite(MyArray<T>& myArray)
{
	stringstream out;
	unsigned int count = 0;
	out << "COMPOSITE: " << endl;
	MyArray<int>::Iterator iter = myArray.begin();
	MyArray<int>::Iterator iterend = myArray.end();
	for (int i = 0; iter != iterend; ++iter)
	{
		if (count != 0 && count % 10 == 0)
		{
			out << endl;
			count = 0;
		}
		if (!isPrime(*iter) && *iter != 1)
		{
			out << *iter << " ";
			count++;
		}
	}
	out << endl << endl;
	return out.str();
}


template<typename T>
string printFibonacci(MyArray<T>& myArray)
{
	stringstream out;
	MyArray<int>::Iterator iter_prev_prev = myArray.begin();		//index - 2
	MyArray<int>::Iterator iter_prev = myArray.begin();				//index -1
	MyArray<int>::Iterator iter_curr = myArray.begin();				//index
	MyArray<int>::Iterator iterend = myArray.end();

	out << "FIBONACCI: " << endl;

	for (int i = 0; iter_curr != iterend; ++iter_curr)
	{
		if (i == 1)
			++iter_prev;
		else if (i >= 2)
		{
			//Check for Fibonacci number
			if (*iter_prev_prev + *iter_prev == *iter_curr)
				out << *iter_curr << " = " << *iter_prev_prev << " + " << *iter_prev << endl;
			++iter_prev_prev;
			++iter_prev;
		}
		else
		{
		}

		i++;
	}
	out << endl << endl;
	return out.str();
}

/******** END OF METHODS *******/


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

	//Input file content to our templated class
	MyArray<int> myArray(ARRAY_SIZE);

	int i;
	size_t count = 0;
	while (in >> i)
	{
		myArray.push_back(i);
		count++;
	}

	//Set iterator to start of array
	MyArray<int>::Iterator iter = myArray.begin();
	// cout << endl;

	//Print myArray
	out << printMyArray(myArray);

	//Print ITERATORS
	out << printIterator(myArray);

	//Print SEQUENTIAL
	out << printSequential(myArray);

	//Print PRIME
	out << printPrime(myArray);

	//Print COMPOSITE
	out << printComposite(myArray);

	//Print FIBONACCI
	out << printFibonacci(myArray);



	//Free memory
	myArray.Free();
	if (!CONSOLE)
	{
		ofstream * pout = (ofstream *)&out;
		pout->close();
		delete pout;
	}
}
