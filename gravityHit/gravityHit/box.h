#pragma once
#include "objBase.h"

class CBox :public BaseVector
{
public:
	CBox();

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();

	Point mid_pos{ 0,0 };		//���̂̒��S���W

	Vector unit_v{ 1,0 };		//�P�ʃx�N�g��
	Vector angle_w{ 0,0 };		//�����x�N�g��
	Vector angle_h{ 0,0 };		//�c���x�N�g��

	int radian;					//��]�p�x
};