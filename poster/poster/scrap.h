#pragma once
#include "objBase.h"

class CScrap :public BaseVector
{
public:
	CScrap(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float g{ 0.5f };
};