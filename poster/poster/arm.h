#pragma once
#include "objBase.h"

class CArm :public BaseVector
{
public:
	CArm();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	int GRAP_TIME = 30;

	bool arm_down{ false };
	bool arm_grap{ false };
	
	int move_time{ 0 };

	enum HIT_BUTTON
	{
		A,
		D,
		F,
		HBEND
	};

	bool Click_Check[HBEND];
};