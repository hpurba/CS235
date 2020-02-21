#ifndef DEQUE_H
#define DEQUE_H
#include <string>
#include "DequeInterface.h"

using std::string;

template<typename T>
class DeQue :public DequeInterface<T>
{
	//static const size_t DEFAULT_CAPACITY = 4
private:
	size_t capacity;
	size_t num_items;
	size_t front_index;
	size_t rear_index;
	T* the_data;
	void reallocate();


public:
	DeQue(void);
	~DeQue();
	void push_front(const T& item);
	void push_back(const T& item);
	void pop_front(void);
	void pop_back(void);
	T& front();
	T& back();
	size_t size()const;
	bool empty()const;
	T& at(size_t index);
	string toString()const;
};

template<typename T>
DeQue<T>::DeQue(void)
{
	capacity = DEFAULT_CAPACITY;
	num_items = 0;
	front_index = 0;
	rear_index = 0;
	the_data = new T[DEFAULT_CAPACITY];
}

template<typename T>
DeQue<T>::~DeQue()
{
	delete[] the_data;
}

template<typename T>
void DeQue<T>::reallocate()
{
	size_t newSize = capacity * 2;
	T* tempCircular = new T[newSize];
	//Copy the_data to new location
	size_t normalizedIndex = front_index;
	for (size_t i = 0; i < num_items; i++)
	{
		if (normalizedIndex > (capacity - 1))
			normalizedIndex = 0;
		tempCircular[i] = the_data[normalizedIndex];
		normalizedIndex++;
	}

	//Update capacity
	capacity = newSize;
	//Destroy old pointer
	delete[] the_data;
	//Assign new location to the_data
	the_data = tempCircular;
	front_index = 0;
	rear_index = num_items - 1;
}

template<typename T>
void DeQue<T>::pop_front(void)
{
	if (num_items != 0)
	{
		++front_index;
		if (front_index >= capacity)
			front_index = 0;
		num_items = num_items - 1;
		if (num_items == 0)
			front_index = rear_index = 0;
	}

}

template<typename T>
void DeQue<T>::pop_back(void)
{
	if (num_items != 0)
	{
		if (rear_index == 0)
			rear_index = capacity - 1;
		else
			rear_index--;
		num_items = num_items - 1;
		if (num_items == 0)
			front_index = rear_index = 0;
	}
}

template<typename T>
void DeQue<T>::push_front(const T& item)
{
	if ((num_items + 1) > capacity)
		reallocate();

	if (num_items != 0)
	{
		//If front Index is already zero before pushing front, then set front index to last place
		if (front_index == 0)
			front_index = capacity - 1;
		else
			front_index--;
	}

	the_data[front_index] = item;
	num_items = num_items + 1;
}

template<typename T>
void DeQue<T>::push_back(const T& item)
{
	if ((num_items + 1) > capacity)
		reallocate();
	if (num_items != 0)
		++rear_index;
	if (rear_index > (capacity - 1))
		rear_index = 0;
	the_data[rear_index] = item;
	num_items = num_items + 1;
}

template<typename T>
T& DeQue<T>::front()
{
	return the_data[front_index];
}

template<typename T>
T& DeQue<T>::back()
{

	return the_data[rear_index];
}

template<typename T>
size_t DeQue<T>::size()const
{
	return num_items;
}

template<typename T>
bool DeQue<T>::empty()const
{
	bool bEmpty = false;
	if (num_items == 0)
		bEmpty = true;
	return bEmpty;
}

template<typename T>
T& DeQue<T>::at(size_t index)
{
	size_t normalizedIndex = front_index + index;
	if (normalizedIndex > (capacity - 1))
		normalizedIndex -= capacity;
	return the_data[normalizedIndex];
}

template<typename T>
string DeQue<T>::toString()const
{
	string ssomething;
	return ssomething;
};
#endif // DEQUE_H
