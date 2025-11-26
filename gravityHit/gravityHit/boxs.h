#pragma once
#include "objBase.h"

class CBoxs :public BaseVector
{
public:
	CBoxs();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	float g{ 0.5f };
	int x, y;
	int ClickX, ClickY;

	BoxLine line[4];

	bool click{ false };

	Vector rad_vec;
	Vector I;
	Vector power;
	Vector distance;
	float resultpower;
};