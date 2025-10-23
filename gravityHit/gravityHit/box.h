#pragma once
#include "objBase.h"

class CBox :public BaseVector
{
public:
	CBox();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	Point mid_pos{ 0,0 };		//物体の中心座標

	Vector unit_v{ 1,0 };		//単位ベクトル
	Vector angle_w{ 0,0 };		//横幅ベクトル
	Vector angle_h{ 0,0 };		//縦幅ベクトル

	int radian;					//回転角度
};