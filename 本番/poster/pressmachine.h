#pragma once
#include "objBase.h"

class CPressmachine :public BaseVector
{
public:
	CPressmachine();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	bool press_start{ false };
	bool bottom_hit{ false };
	bool can_press{ false };
	bool reverse{ false };
	bool more_press{ false };

	float speed{ 3.0f };

	Point Bottom{ 0,0 };
	Vector Bhit_Size{ 0,0 };
	Point Top{ 0,0 };
	Vector Thit_Size{ 0,0 };
};