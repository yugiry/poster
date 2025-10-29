#pragma once
#include "objBase.h"

class CCircle :public BaseVector
{
public:
	CCircle();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float bound{ 0.5f };

	float g{ 0.5f };

	Vector vv1{ 0,0 };
	Vector vv2{ 0,0 };

	Point p{ 0,0 };
};