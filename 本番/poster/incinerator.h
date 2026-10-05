#pragma once
#include "objBase.h"

class CIncinerator :public BaseVector
{
public:
	CIncinerator();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};