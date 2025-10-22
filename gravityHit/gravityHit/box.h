#pragma once
#include "objBase.h"

class CBox :public BaseVector
{
public:
	CBox();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};