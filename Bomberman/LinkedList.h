#pragma once

template <class T>
class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();

	//Adds the element to the kth position
	void add(T, int);

	//Add the element to the back of the list
	void push_back(T);


	//Removes the kth element from the list
	T remove(int);

	//Returns the nth element of the list
	T get(int);

	int size();

	bool empty();

	void iterator();

	bool isNull();

	void next();

	void prev();

	T curr();

	void destroy();

protected:
	struct node {
		T val;
		node *next = nullptr;
		node *prev = nullptr;
	};
	node *first;
	node *last;
	node *iter;
	int length;
};