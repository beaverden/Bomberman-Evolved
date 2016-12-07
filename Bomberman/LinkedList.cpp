#include "LinkedList.h"


template <class T>
LinkedList <T>::LinkedList()
{
	this->first = nullptr;
	this->last = nullptr;
	this->length = 0;
}

template <class T>
LinkedList <T>::~LinkedList()
{
}

template <class T>
void LinkedList<T>::add(T val, int pos)
{
	node *newNode = new node;
	newNode->val = val;
	if (this->length == 0)
	{
		if (pos == 0)
		{
			this->first = new node;
			this->first->val = val;
			this->last = this->first;
		}
	}
	else if (pos == this->length)
	{
		newNode->prev = this->last;
		this->last->next = newNode;
		this->last = newNode;

	}
	else if (pos == 0)
	{
		newNode->next = this->first;
		this->first->prev = newNode;
		this->first = newNode;
	}
	else
	{
		node* iterNode = this->first;
		int k = 0;
		while (iterNode && k < pos)
		{
			iterNode = iterNode->next;
			k++;
		}

		if (iterNode->prev)
		{
			iterNode->prev->next = newNode;
		}
		newNode->prev = iterNode->prev;

		iterNode->prev = newNode;
		newNode->next = iterNode;
	}
	this->length++;
	newNode = nullptr;
}


template <class T>
void LinkedList<T>::push_back(T val)
{
	this->add(val, this->size());
}


template <class T>
T LinkedList<T>::remove(int k)
{
	T returnValue;

	if (k == 0)
	{
		returnValue = this->first->val;
		node *nextLink = this->first->next;
		delete this->first;
		if (this->length == 1)
		{
			this->first = nullptr;
			this->last = nullptr;
			this->iter = nullptr;
		}
		else
		{
			nextLink->prev = nullptr;
			this->first = nextLink;
		}
		nextLink = nullptr;
	}
	else if (k == this->length - 1)
	{
		returnValue = this->last->val;
		node *prevLink = this->last->prev;
		delete this->last;
		if (this->length == 1)
		{
			this->first = nullptr;
			this->last = nullptr;
			this->iter = nullptr;
		}
		else
		{
			prevLink->next = nullptr;
			this->last = prevLink;
		}
		prevLink = nullptr;
	}
	else
	{
		node* iterator = this->first;
		int  currentPosition = 0;
		while (iterator && currentPosition < k)
		{
			iterator = iterator->next;
			currentPosition++;
		}
		returnValue = iterator->val;
		iterator->prev->next = iterator->next;
		delete iterator;
		iterator = nullptr;
	}
	this->length--;
	return returnValue;
}


template <class T>
T LinkedList<T>::get(int n)
{
	int k = 0;
	node *it = this->first;
	while (it && k < n)
	{
		it = it->next;
		k++;
	}
	return it->val;
}


template <class T>
int LinkedList<T>::size()
{
	return this->length;
}


template <class T>
bool LinkedList<T>::empty()
{
	return (this->length == 0);
}


template <class T>
void LinkedList<T>::iterator()
{
	this->iter = this->first;
}


template <class T>
bool LinkedList<T>::isNull()
{
	return (this->iter == nullptr);
}


template <class T>
void LinkedList<T>::next()
{
	if (this->iter)
	{
		this->iter = this->iter->next;
	}
}


template <class T>
void LinkedList<T>::prev()
{
	if (this->iter)
	{
		this->iter = this->iter->prev;
	}
}


template <class T>
T LinkedList<T>::curr()
{
	return this->iter->val;
}


template <class T>
void LinkedList<T>::destroy()
{
	while (!this->empty())
	{
		this->remove(0);
	}
	this->first = nullptr;
	this->last = nullptr;
	this->iter = nullptr;
}