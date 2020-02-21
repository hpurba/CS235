#ifndef MYQUEUE_H
#define MYQUEUE_H
#include "Deque.h"

using namespace std;

template<typename T>
class MyQueue
{
private:
	DeQue<T> container_;
public:
	MyQueue() {};
	~MyQueue() {};
	string push(const T& item);
	void pop();
	T& top();
	size_t size();
	T& at(size_t index);
	string toString()const;
};

template<typename T>
string MyQueue<T>::push(const T& item)
{
	string alwaysSuccess = "Always successful";
	container_.push_back(item);
	return alwaysSuccess;
}

template<typename T>
void MyQueue<T>::pop()
{
	container_.pop_front();
}

template<typename T>
T& MyQueue<T>::top()
{
	//Queue is First-In-First-Out, any push
	//is a push back, and any pop is a pop_back
	//The top then is the back.
	return container_.front();
}

template<typename T>
size_t MyQueue<T>::size()
{
	return container_.size();
}

template<typename T>
T& MyQueue<T>::at(size_t index)
{
	return container_.at(index);
}

template<typename T>
string MyQueue<T>::toString()const
{
	string sRe = "";
	return sRe;
}
#endif // MYQUEUE_H
