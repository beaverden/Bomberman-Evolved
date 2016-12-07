#pragma once

#include "LinkedList.h"
template <class T>
class Stack :
	public LinkedList <T>
{
public:

	Stack() : LinkedList() {}

	~Stack() {}

	void push(T val)
	{
		this->add(val, 0);
	}

	T pop()
	{
		return this->remove(0);
	}

	T top()
	{
		return this->get(0);
	}
};

