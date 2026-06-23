#pragma once
#include "objBase.h"

class CBox :public BaseVector
{
public:
	CBox();

	int Action(const ObjList&, ObjList&);
	void Draw();
};