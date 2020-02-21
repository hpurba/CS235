#ifndef MYSTACK_H
#define MYSTACK_H
#include "Deque.h"
using namespace std;

template<typename T>
class MyStack
{
private:
	DeQue<T> container_;

public:
	MyStack() {};
	~MyStack() {};
	string push(const T& item);
	void pop();
	T& top();
	size_t size();
	T& at(size_t index);
	string toString()const;

};

template <typename T>
string MyStack<T>::push(const T& item)
{
	string alwaysSuccess = "always successful";
	container_.push_back(item);
	return alwaysSuccess;
}

template<typename T>
void MyStack<T>::pop()
{
	if (container_.size() != 0)
		container_.pop_back();
	else
		cout << "Stack is empty";
}

template<typename T>
T& MyStack<T>::top()
{
	return container_.back();
}

template<typename T>
size_t MyStack<T>::size()
{
	return container_.size();
}

template<typename T>
T& MyStack<T>::at(size_t index)
{
	return container_.at(index);
}

template<typename T>
string MyStack<T>::toString()const
{
	string s = "hello";
	return s;
}

#endif // MYSTACK_H

