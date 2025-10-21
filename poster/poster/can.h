#pragma once
#include "objBase.h"

class CCan :public BaseVector
{
public:
	CCan(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float g{ 0.5f };
};