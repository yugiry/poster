#pragma once
#include "objBase.h"

class CObject :public BaseVector
{
public:
	CObject(int);

	int Action(const ObjList&, ObjList&);
	void Draw();
};