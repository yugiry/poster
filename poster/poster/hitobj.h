#pragma once
#include "objBase.h"

class CHitobj :public BaseVector
{
public:
	//���W�A�����A�c��
	CHitobj(Point, int, int);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};