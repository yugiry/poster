#pragma once
#include "objBase.h"

class CCircle :public BaseVector
{
public:
	CCircle();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float g{ 0.5f };
};