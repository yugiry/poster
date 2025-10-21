#pragma once
#include "objBase.h"

class CPressmachine :public BaseVector
{
public:
	CPressmachine();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};