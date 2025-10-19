#pragma once
#include "objBase.h"

class CHitobj :public BaseVector
{
public:
	CHitobj(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};