#pragma once
#include "objBase.h"

class CBoxs :public BaseVector
{
public:
	CBoxs();
	CBoxs(Point, int, int);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	enum BOXPOINT
	{
		LEFTUP,
		RIGHTUP,
		LEFTDOWN,
		RIGHTDOWN
	};

	float g{ 0.5f };
	int x, y;
	int ClickX, ClickY;

	Point BoxPoint[4];
	
	BoxLine line;

	bool click{ false };
};