#pragma once
template <class A, class B>
class Pair
{
public:

	Pair()
	{

	}

	Pair(A first, B second)
	{
		this->firstElement = first;
		this->secondElement = second;
	}

	~Pair()
	{
	}

	A first()
	{
		return this->firstElement;
	}

	B second()
	{
		return this->secondElement;
	}

	void setFirst(A newFirst)
	{
		this->firstElement = newFirst;
	}

	void setSecond(A newSecond)
	{
		this->secondElement = newSecond;
	}

	Pair operator()(A _first, B _second)
	{
		Pair p(_first, _second);
		return p;
	}

private:
	A firstElement;
	B secondElement;
};

