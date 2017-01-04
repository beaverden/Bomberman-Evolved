#pragma once
class Box
{
public:
	Box();
	Box(float x, float y, float w, float h);
	~Box();

	Box operator()(float x, float y, float w, float h);
	bool operator==(const Box& other);
	bool operator!=(const Box& other);	

	float x;
	float y;
	float w;
	float h;
};

