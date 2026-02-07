#pragma once
#include "objBase.h"

class CCircles :public BaseVector
{
public:
	CCircles();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};