#pragma once
#include "objBase.h"

class CLine :public BaseVector
{
public:
	CLine();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};