#pragma once
#include "objBase.h"

class CWall :public BaseVector
{
public:
	CWall(Point, int, int);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};