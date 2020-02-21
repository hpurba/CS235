#ifndef SET_H
#define SET_H
#include "SetInterface.h"

using std::string;

template<typename T>
class Set :public SetInterface<T>
{
private:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
		Node(const T& d) : data(d), left(NULL), right(NULL) {};
	};
	Node* head;

	bool findNode(Node* node, const T& data);
	//Insert a node appropriately
	bool insertNode(Node*& node, const T& data);
	//Delete all nodes starting from left to right recursively
	bool deleteAllNodes(Node*& node);
	//Find a node to delete
	bool findNodetoDelete(Node*& node, const T& data);
	//Find largest or equal to and swap
	T findLargestandSwap(Node*& node, const T datatoExchange);

	bool outLevel(Node* root, int level, std::stringstream& out) const;

public:
	Set(void) { this->head = NULL; }
	~Set(void) { clear(); }
	class Iterator
	{
	private:
		// private iterator state...
		Node* root_;
		mutable int index_;
		bool getDatafromIndex(Node* node, int& currentIndex, T& value);
		//Helper function to traverse the tree
		T traversetoIndex();


	public:
		Iterator(Node* root, int index) : root_(root), index_(index) {};
		~Iterator() {};
		bool operator!=(const Iterator& rhs) const;
		T operator*();
		Iterator operator++(int);
		bool getIndexfromData(Node* node, int& index, T& value);
		int traversetoData(T value);
	};

	Iterator begin() const;
	Iterator end() const;
	Iterator Find(T& item);

	//Count number of nodes
	void NumberNodes(Node* node, int& count)const;

	//Customer facing method. This is what customer will call to delete a node
	bool removeNode(const T& item);



	//SETINTERFACE implementation of the class
	/** Return true if node added to Set, else false */
	bool insert(const T& item);

	//Customer facing method. This method deletes all nodes.
	void clear();

	/** Return a level order traversal of a Set as a string */
	string toString()const;

	//Customer facing method
	size_t count(const T& data);

	//Customer facing method
	size_t size()const;

};


//PRIVATE
template<typename T>
int Set<T>::Iterator::traversetoData(T value)
{
	int index = -1;
	bool bFound = false;
	if (root_)
		bFound = getIndexfromData(root_, index, value);

	//If not found, match the index to the end()
	if (!bFound)
		index++;
	return index;
}

//PRIVATE
template<typename T>
T Set<T>::Iterator::traversetoIndex() {
	int passedIn = index_ + 1;
	T value;
	bool bFound = getDatafromIndex(root_, passedIn, value);
	return value;
}

//PRIVATE
template<typename T>
bool Set<T>::Iterator::getIndexfromData(Node* node, int& index, T& value)
{
	bool bFound = false;

	if (node->left)
		bFound = getIndexfromData(node->left, index, value);
	index = index + 1;
	if (!bFound)
	{
		if (node->data == value)
			return true;
		if (node->right)
		{
			bFound = getIndexfromData(node->right, index, value);
			return bFound;
		}
		return false;
	}
	else
		return true;
}

//PRIVATE
template<typename T>
bool Set<T>::Iterator::getDatafromIndex(Node* node, int& currentIndex, T& value)
{
	bool bFound = false;
	//always traverse to the left first
	if (node->left)
		bFound = getDatafromIndex(node->left, currentIndex, value);

	//Decrement count
	currentIndex = currentIndex - 1;

	if (!bFound)
	{
		//if counter reaches 0, then it is the node where the data is located.
		if (currentIndex == 0)
		{
			value = node->data;
			return true;
		}
		//If the data is not found, then we start looking to the right.
		if (node->right)
		{
			bFound = getDatafromIndex(node->right, currentIndex, value);
			return bFound;
		}
		return false;
	}
	else
		return true;
}


//PRIVATE
template<typename T>
bool Set<T>::outLevel(Node* root, int level, std::stringstream& out) const
{
	if (root == NULL)
		return false;
	if (level == 1)
	{
		out << " " << root->data;
		if ((root->left != NULL) || (root->right != NULL)) return true;
		return false;
	}
	if ((level == 2) && !root->left && root->right)
		out << " _";
	bool left = outLevel(root->left, level - 1, out);
	bool right = outLevel(root->right, level - 1, out);
	if ((level == 2) && root->left && !root->right)
		out << " _";
	return left || right;
} // end outLevel()

//PRIVATE
template<typename T>
void Set<T>::NumberNodes(Node* node, int& count)const
{
	if (node)
	{
		count++;
		if (node->left)
			NumberNodes(node->left, count);
		if (node->right)
			NumberNodes(node->right, count);
	}
}

//PRIVATE
template<typename T>
bool Set<T>::findNode(Node* node, const T& data)
{
	if (node->data == data)
		return true;
	else if (node->data < data)
	{
		//Check right
		if (node->right)
			return findNode(node->right, data);
		else
			return false;
	}
	else
	{
		//Check left
		if (node->left)
			return findNode(node->left, data);
		else
			return false;
	}
}

//PRIVATE
template<typename T>
bool Set<T>::insertNode(Node*& node, const T& data)
{
	if (!node)
	{
		node = new Node(data);
		return true;
	}
	else
	{
		if (node->data > data)
		{
			return insertNode(node->left, data);
		}
		else if (node->data < data)
		{
			return insertNode(node->right, data);
		}
		else
			return false;
	}
}

//PRIVATE
template<typename T>
bool Set<T>::deleteAllNodes(Node*& node)
{
	if (!node)
		return true;
	else
	{
		bool bLeftDeleted = false;
		bool bRightDeleted = false;
		if (node->left)
		{
			bLeftDeleted = deleteAllNodes(node->left);
			node->left = NULL;
		}
		if (node->right)
		{
			bRightDeleted = deleteAllNodes(node->right);
			node->right = NULL;
		}
		delete node;
		return true;
	}

}

//PRIVATE
template<typename T>
T Set<T>::findLargestandSwap(Node*& node, const T datatoExchange)
{
	if (node->right)
		return findLargestandSwap(node->right, datatoExchange);
	else
	{
		T largestData = node->data;
		node->data = datatoExchange;
		return largestData;
	}
}

//PRIVATE
template<typename T>
bool Set<T>::findNodetoDelete(Node*& node, const T& data)
{
	//Node does not exists, return error
	if (!node)
		return false;
	//current node data is less than seeked, then go to right
	if (node->data < data)
		return findNodetoDelete(node->right, data);
	//current node data is greater than seeked, then go to left
	if (node->data > data)
		return findNodetoDelete(node->left, data);
	if (node->data == data)
	{
		if (node->left == NULL && node->right == NULL)
		{
			delete node;
			node = NULL;
			return true;
		}
		else if (node->left == NULL && node->right != NULL)
		{
			Node* tempNode = node->right;
			delete node;
			node = tempNode;
			return true;
		}
		else if (node->left != NULL && node->right == NULL)
		{
			Node* tempNode = node->left;
			delete node;
			node = tempNode;
			return true;
		}
		else
		{
			node->data = findLargestandSwap(node->left, data);
			return findNodetoDelete(node->left, data);
		}
	}
	return false;
}




template<typename T>
typename Set<T>::Iterator Set<T>::Find(T& item)
{
	Set<T>::Iterator tempIterator = Set<T>::Iterator(head, 0);
	int index = tempIterator.traversetoData(item);
	return Set<T>::Iterator(head, index);
}

template<typename T>
typename Set<T>::Iterator Set<T>::Iterator::operator++(int)
{
	index_ = index_ + 1;
	return Set<T>::Iterator(root_, index_);
};

template<typename T>
T Set<T>::Iterator::operator*() {
	return traversetoIndex();
};

template<typename T>
bool Set<T>::Iterator::operator!=(const Iterator& rhs) const
{
	return rhs.index_ != index_;
};

template<typename T>
bool Set<T>::insert(const T& item)
{
	return insertNode(head, item);
}

template<typename T>
size_t Set<T>::count(const T& data)
{
	size_t found = 0;
	if (findNode(head, data))
		found = 1;
	return found;
}

template<typename T>
size_t Set<T>::size()const
{
	int count = 0;
	NumberNodes(head, count);
	return size_t(count);
}

template<typename T>
bool Set<T>::removeNode(const T& item)
{
	return findNodetoDelete(head, item);
}

template<typename T>
void Set<T>::clear()
{
	bool Setatus = deleteAllNodes(head);
	head = NULL;
}


template<typename T>
string Set<T>::toString()const
{
	std::stringstream out;
	Iterator iter = begin();
	Iterator iterend = end();
	if (!(iter != iterend))
		out << "empty";
	else
	{
		for (int i = 0; iter != iterend; iter++)
		{
			if (i != 0)
				out << ",";
			out << *iter;
			i++;
		}
	}
	return out.str();
}

template<typename T>
typename Set<T>::Iterator Set<T>::begin() const {
	return Set<T>::Iterator(head, 0);
};


template<typename T>
typename Set<T>::Iterator Set<T>::end() const
{
	int count = 0;
	NumberNodes(head, count);
	return Set<T>::Iterator(head, count);
};

#endif