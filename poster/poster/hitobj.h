#pragma once
#include "objBase.h"

class CHitobj :public BaseVector
{
public:
	//座標、移動力、横幅、縦幅、生存時間、ＩＤ
	CHitobj(Point, Vector, int, int, int, int);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int alive_time{ -1 };
	float g{ 0.5f };
};