#pragma once
#include "objBase.h"

class CPaper :public BaseVector
{
public:
	CPaper(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int img{-1};
	float g{ 0.5f };
	Point dpos{ 0,0 };
};