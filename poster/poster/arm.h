#pragma once
#include "objBase.h"

class CArm :public BaseVector
{
public:
	CArm(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};