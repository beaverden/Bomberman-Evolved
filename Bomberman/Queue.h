#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "LinkedList.h"

template <class T>
class Queue :
	public LinkedList <T>
{
public:

	Queue() : LinkedList() {}

	~Queue() {}

	void push(T val)
	{
		this->add(val, this->size());
	}

	T pop() {
		return this->remove(0);
	}

	T front()
	{
		return this->get(0);
	}
};

#endif /* QUEUE_H */


