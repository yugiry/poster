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
		RIGHTDOWN,
		LEFTDOWN
	};

	float g{ 0.5f };
	int x, y;
	int ClickX, ClickY;

	Vector vertex_vec[4];
	BoxLine near_line;

	Vector normal_force;	//êÇíºçRóÕ
	Vector radian_force;	//âÒì]óÕ

	Vector mid_point_vec;

	float force_radian{ 0 };

	bool click{ false };
	bool hit{ false };
	bool radian_click{ false };
};