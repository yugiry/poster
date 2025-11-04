#pragma once
#include "objBase.h"

class CBoxs :public BaseVector
{
public:
	CBoxs();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int radian{ 330 };
	float g{ 0.5f };

	Point line[4];
};