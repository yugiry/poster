#pragma once
#include "objBase.h"

class CHitobj :public BaseVector
{
public:
	CHitobj();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};