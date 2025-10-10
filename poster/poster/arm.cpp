#pragma once
#include "arm.h"

CArm::CArm()
{
	//�A�[���̏����ʒu
	pos.x = 0;
	pos.y = 20;

	//�A�[���̉摜�T�C�Y
	ImgWidth = 64;
	ImgHeight = 64;

	//�{�^����������Ă��邩����̏�����
	for (int i = 0; i < HBEND; i++)
	{
		Click_Check[i] = false;
	}
}

int CArm::Action(vector<unique_ptr<BaseVector>>& base)
{
	//�ړ��������Z�b�g
	vec.x = vec.y = 0;

	if (move_time != 0)move_time--;
	if (move_time == 0)
	{
		move_time--;
	}

	//�A�[����������
	if (CheckHitKey(KEY_INPUT_F) && !Click_Check[F] && !arm_down)
	{
		arm_down = true;
	}

	//�A�[�����������Ă��Ȃ���
	if (!arm_down && pos.y <= 20 && move_time < 0)
	{
		if (CheckHitKey(KEY_INPUT_A) && !Click_Check[A])
		{
			vec.x = -3.0f;
		}
		if (CheckHitKey(KEY_INPUT_D) && !Click_Check[D])
		{
			vec.x = 3.0f;
		}
	}

	//�A�[����������
	if (arm_down)
	{
		vec.y = 4.0f;
	}
	//�A�[����������
	if (!arm_down && pos.y > 20 && move_time < 0)
	{
		vec.y = -4.0f;
	}

	//�A�[�������ɓ���
	if (pos.y + vec.y + ImgWidth > WINDOW_HEIGHT)
	{
		arm_down = false;
		move_time = GRAP_TIME;
		vec.y -= 4.0f;
	}

	//���W�X�V
	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CArm::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 0, 0), true);
}