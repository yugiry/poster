#pragma once
#include "objBase.h"

class CHitobj :public BaseVector
{
public:
	//À•WA‰¡•Ac•
	CHitobj(Point, int, int);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};