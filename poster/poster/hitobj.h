#pragma once
#include "objBase.h"

class CHitobj :public BaseVector
{
public:
	//���W�A�ړ��́A�����A�c���A�������ԁA�h�c
	CHitobj(Point, Vector, int, int, int, int);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int alive_time{ -1 };
	float g{ 0.5f };
};