#pragma once
#include "objBase.h"

class CBox :public BaseVector
{
public:
	CBox();
	CBox(Point);

	int Action(const ObjList&, ObjList&);
	void Draw();

	bool can_move{ false };
};