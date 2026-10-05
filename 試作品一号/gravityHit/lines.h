#pragma once
#include "objBase.h"

class CLines :public BaseVector
{
public:
	CLines();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};