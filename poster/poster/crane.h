#pragma once
#include "objBase.h"

#include "arm.h"

class CCrane :public BaseVector
{
public:
	CCrane();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	//アームが閉じるまでの時間
	int GRAP_TIME = 30;

	bool arm_down{ false };		//アームが下がっているか

	//アームの開閉
	int open_time{ -1 };		//アームを開くまでの時間の計測用
	int close_time{ -1 };		//アームを閉じるまでの時間の計測用

	bool arm_state{ false };	//アームが開いているか閉じているか

	int move_time{ -1 };		//アームが移動している時間の計測
	int arm_open{ -1 };			//アームが開くまでの時間の計測

	enum HIT_BUTTON
	{
		A,
		D,
		F,
		HBEND
	};

	bool Click_Check[HBEND];

	CArm* Larm;
	CArm* Rarm;
};