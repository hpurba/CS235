#ifndef QS_H
#define QS_H
#include "QSInterface.h"
using std::string;
using std::ostream;

template<typename T>
class QuickSort :public QSInterface<T>
{
	private:
		string command; // what is asked of
		size_t mSize;		// size of occupied cells
		int *myArray;	// myArray
		int value;		// value to insert into array
		// size_t mCapacity; // capacity is how big the array is
		
	public:
		// QuickSort(void) {}; // Constructor?
		// ~QuickSort(); // Destructor
		bool createArray(size_t capacity);
		bool clear() const;
		// bool addElement(T element);
		// bool setValue(int position int value); // Set the values in the array.
		size_t capacity() const;
		// bool addElement(T element);
		size_t getsize() const;

};

template<typename T>
bool QuickSort<T>::createArray(size_t capacity) {
	delete[] myArray;
	mSize = capacity;
	// must copy information into new array and delete the old one.
	int* myArray = new int[mSize];
	return true;
};


template<typename T>
size_t QuickSort<T>::capacity() const {
	size_t capacity = getsize();
	return capacity;
};

template<typename T>
size_t QuickSort<T>::getsize() const {
	return mSize;
};

template<typename T>
bool QuickSort<T>::clear() const {
	delete[] myArray;
	return true;
};

/*
template<typename T>
bool QuickSort<T>::addElement(T element) {
	size_t capacity = getsize();
	for (size_t i = 0; i < capacity; i++) {
		if (myArray) {
			myArray[i] = element;
			return true;
		}
	}
}
*/

















// Create array?
/*
template<typename T>
QuickSort<T>::QuickSort(int size) 
{
	int SIZE = size;
	int* myArray = NULL;
	myArray = new int[SIZE];

}
*/



// Delete array
/*
template<typename T>
QuickSort<T>::~QuickSort()
{
	delete[] myArray;
	myArray = NULL;
}
*/


/*
template<typename T>
bool QuickSort<T>::addElement(T element)
{
	// check how big the array is.
	int position = 0;
	myArray[position] = element;
	return true;
}
*/


#endif