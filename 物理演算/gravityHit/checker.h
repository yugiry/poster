#pragma once
#include "objBase.h"
#include "function.h"

class CChecker :public BaseVector
{
public:
	CChecker();
	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};