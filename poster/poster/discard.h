#pragma once
#include "objBase.h"

class CDiscard :public BaseVector
{
public:
	CDiscard();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};