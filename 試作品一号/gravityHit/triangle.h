#pragma once
#include "objBase.h"

class CTriangle :public BaseVector
{
public:
	CTriangle();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};