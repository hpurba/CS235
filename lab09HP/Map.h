#ifndef MAP_H
#define MAP_H
#include <math.h>
#include "Set.h"
#include "HashMapInterface.h"

using namespace std;

template<typename string, typename V>
class HashNode
{
public:
	string key_;
	V value_;
	HashNode();
	virtual string toString() {
		string s;
		return s;
	};
};

//specialize toString for <string, string>
template<>
string HashNode<string, string>::toString() { return this->value_; };


//specialize toString for <string, Set<string>>
template<>
string HashNode<string, Set<string>>::toString()
{
	return this->value_.toString();
}




template<typename string, typename V>
class Map :public HashMapInterface<string, V>
{
private:
	HashNode<string, V> **hashnode;
	size_t capacity;
	size_t keyToIndex(const string& key);

public:
	Map();
	~Map();
	V& operator[](const string& key);

	/** @return: the number of elements that match the key in the Map. */
	size_t count(const string& key);

	/** Removes all items from the Map. */
	void clear();

	/** @return: number of Key-Value pairs stored in the Map. */
	size_t size() const;

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	size_t max_size() const;

	/** @return: string representation of Key-Value pairs in Map. */
	string toString() const;

	void reallocate();
};


template<typename string, typename V>
HashNode<string, V>::HashNode()
{
	this->key_ = "";
}



template<typename string, typename V>
Map<string, V>::Map()
{
	hashnode = new HashNode<string, V>*[DEFAULT_MAP_HASH_TABLE_SIZE];

	for (size_t i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++)
		hashnode[i] = new HashNode<string, V>;

	capacity = DEFAULT_MAP_HASH_TABLE_SIZE;
}

template<typename string, typename V>
Map<string, V>::~Map()
{
	clear();
}

template<typename string, typename V>
void Map<string, V>::reallocate()
{
	//if number of elements/capacity is greater than LOAD_THRESHOLD then reallocate
	//if ((size() * 100) > (capacity * LOAD_THRESHOLD)) This LOAD_THRESHOLD value does not work, so it is changed from 75 to 79
	if ((size() * 100) > (capacity * 79))
	{
		size_t doubleCapacity = capacity << 1;

		HashNode<string, V> **tempNode;
		tempNode = new HashNode<string, V>*[doubleCapacity];
		for (size_t i = 0; i < doubleCapacity; i++)
			tempNode[i] = new HashNode<string, V>;

		//Rehash every entry
		for (size_t j = 0; j < capacity; j++)
		{
			if (hashnode[j]->key_ != "")
			{
				string key = hashnode[j]->key_;
				size_t computedIndex = keyToIndex(key) % doubleCapacity;
				unsigned int loop = 0;
				size_t quadraticProbingIndex = 0;
				do
				{
					quadraticProbingIndex = size_t(computedIndex + pow(loop, 2)) % doubleCapacity;
					if (tempNode[quadraticProbingIndex]->key_ == "" || tempNode[quadraticProbingIndex]->key_ == key)
					{
						tempNode[quadraticProbingIndex]->key_ = key;
						break;
					}
					loop++;

				} while (tempNode[quadraticProbingIndex]->key_ != "" && loop < doubleCapacity);
				tempNode[quadraticProbingIndex]->value_ = hashnode[j]->value_;
			}

		}
		//Deletes all entry in hashnode
		clear();
		hashnode = tempNode;

		capacity = doubleCapacity;
	}
}

template<typename string, typename V>
size_t Map<string, V>::keyToIndex(const string& key)
{
	long long Index = 0;
	size_t stringlen = key.size();
	for (size_t i = 0; i < stringlen; i++)
	{
		long long temp = (long long)pow(HASH_CONSTANT, i);
		Index += key[(stringlen - (i + 1))] * temp;
	}
	return Index;
}

//Turns key into index
//If node is not null, it returns a value,
//if it is a null, it creates a new hashnode
template<typename string, typename V>
V& Map<string, V>::operator[](const string& key)
{
	size_t computedIndex = keyToIndex(key) % capacity;
	unsigned int loop = 0;
	size_t quadraticProbingIndex = 0;
	do
	{
		quadraticProbingIndex = size_t(computedIndex + pow(loop, 2)) % capacity;
		if (hashnode[quadraticProbingIndex]->key_ == "" || hashnode[quadraticProbingIndex]->key_ == key)
		{
			hashnode[quadraticProbingIndex]->key_ = key;
			break;
		}
		loop++;

	} while (hashnode[quadraticProbingIndex]->key_ != "" && loop < capacity);
	return hashnode[quadraticProbingIndex]->value_;
}


template<typename string, typename V>
size_t Map<string, V>::count(const string& key)
{
	size_t size = 0;
	return size;
}

template<typename string, typename V>
void Map<string, V>::clear()
{
	for (size_t i = 0; i < capacity; i++)
	{
		HashNode<string, V>* tempNode = hashnode[i];
		delete tempNode;
	}
	delete[] hashnode;
}

template<typename string, typename V>
size_t Map<string, V>::size() const
{
	size_t Count = 0;
	for (size_t i = 0; i < capacity; i++)
	{
		if (hashnode[i]->key_ != "")
			Count++;
	}
	return Count;
}

template<typename string, typename V>
size_t Map<string, V>::max_size()const
{
	return capacity;
}

template<typename string, typename V>
string Map<string, V>::toString()const
{
	stringstream out;
	for (size_t i = 0; i < capacity; i++)
	{
		if (hashnode[i]->key_ != "")
		{
			out << "  [" << i << ": " << hashnode[i]->key_ << "->" << hashnode[i]->toString() << "]" << endl;
		}
	}

	return out.str();
}
#endif