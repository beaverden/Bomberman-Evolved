#pragma once
template <class A, class B>
class Pair
{
public:

	A first;
	B second;

	Pair()
	{

	}

	Pair(A first, B second)
	{
		this->first = first;
		this->second = second;
	}

	~Pair()
	{
	}

	Pair operator()(A _first, B _second)
	{
		Pair p(_first, _second);
		return p;
	}

	bool operator==(const Pair<A, B> &that)
	{
		return (this->first == that.first && this->second == that.second);
	}

	bool operator!=(const Pair<A, B> &that)
	{
		return !(*this == that);
	}

};

