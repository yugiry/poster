#pragma once
#include "objBase.h"

class CArm :public BaseVector
{
public:
	CArm();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	//�A�[��������܂ł̎���
	int GRAP_TIME = 30;

	bool arm_down{ false };		//�A�[�����������Ă��邩

	//�A�[���̊J��
	int open_time{ -1 };		//�A�[�����J���܂ł̎��Ԃ̌v���p
	int close_time{ -1 };		//�A�[�������܂ł̎��Ԃ̌v���p

	bool arm_state{ false };	//�A�[�����J���Ă��邩���Ă��邩

	int move_time{ 0 };			//�A�[�����ړ����Ă��鎞�Ԃ̌v��

	enum HIT_BUTTON
	{
		A,
		D,
		F,
		HBEND
	};

	bool Click_Check[HBEND];
};