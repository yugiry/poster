#pragma once
#include "box.h"
#include "function.h"

CBox::CBox()
{
	pos.x = 100;
	pos.y = 100;

	ImgWidth = 150;
	ImgHeight = 50;

	angle_w = Vector_SetLength(unit_v, ImgWidth);
	angle_h.x = unit_v.y; angle_h.y = unit_v.x;
	angle_h = Vector_SetLength(angle_h, ImgHeight);

	mid_pos.x = Vector_SetLength(angle_w, ImgWidth / 2).x + Vector_SetLength(angle_h, ImgHeight / 2).x;
	mid_pos.y = Vector_SetLength(angle_w, ImgWidth / 2).y + Vector_SetLength(angle_h, ImgHeight / 2).y;

	radian = 0;
}

int CBox::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.x = 0;
	vec.y += 0.5f;

	//�ړ�
	{
		if (CheckHitKey(KEY_INPUT_W))vec.y = -3.0f;
		if (CheckHitKey(KEY_INPUT_S)) vec.y = 3.0f;
		if (CheckHitKey(KEY_INPUT_A)) vec.x = -3.0f;
		if (CheckHitKey(KEY_INPUT_D)) vec.x = 3.0f;
	}

	//��]
	{
		//�����v���
		if (CheckHitKey(KEY_INPUT_U))
		{
			radian -= 3;
		}
		//���v���
		if (CheckHitKey(KEY_INPUT_I))
		{
			radian += 3;
		}

		//��]�̐���
		if (radian <= -1)radian = 359;
		if (radian >= 360)radian = 0;

		//�p�x����X�������߂ăx�N�g���ɑ��
		angle_w.x = cos(RADIAN(radian));
		angle_w.y = sin(RADIAN(radian));
		//90�x��]�������x�N�g������
		angle_h.x = -angle_w.y; angle_h.y = angle_w.x;
		//��������x�N�g���̒����𒲐�
		angle_w = Vector_SetLength(angle_w, ImgWidth);
		angle_h = Vector_SetLength(angle_h, ImgHeight);
	}

	//�ړ�����
	pos.x += vec.x;
	pos.y += vec.y;

	//��ʊO�̓����蔻��
	pos.x = HitLeft(pos, angle_w, angle_h);
	pos.x = HitRight(pos, angle_w, angle_h);
	pos.y = HitUp(pos, angle_w, angle_h);
	pos.y = HitDown(pos, angle_w, angle_h);

	//���S���W�����߂�
	mid_pos.x = pos.x + Vector_SetLength(angle_w, ImgWidth / 2).x + Vector_SetLength(angle_h, ImgHeight / 2).x;
	mid_pos.y = pos.y + Vector_SetLength(angle_w, ImgWidth / 2).y + Vector_SetLength(angle_h, ImgHeight / 2).y;

	return 0;
}

void CBox::Draw()
{
	DrawFormatString(10, 20, GetColor(255, 0, 0), "%d", radian);

	//����
	DrawLine(pos.x, pos.y, pos.x, pos.y - 300, GetColor(0, 255, 0), true);
	//�E��
	DrawLine(pos.x + angle_w.x, pos.y + angle_w.y, pos.x + angle_w.x, pos.y + angle_w.y - 300, GetColor(0, 255, 0), true);
	//����
	DrawLine(pos.x + angle_h.x, pos.y + angle_h.y, pos.x + angle_h.x, pos.y + angle_h.y - 300, GetColor(0, 255, 0), true);
	//�E��
	DrawLine(pos.x + angle_w.x + angle_h.x, pos.y + angle_w.y + angle_h.y, pos.x + angle_w.x + angle_h.x, pos.y + angle_w.y + angle_h.y - 300, GetColor(0, 255, 0), true);
	
	DrawCircle(mid_pos.x, mid_pos.y, 1, GetColor(255, 255, 255), true);

	//��
	DrawLine(pos.x, pos.y, pos.x + angle_w.x, pos.y + angle_w.y, GetColor(255, 255, 255), true);
	//��
	DrawLine(pos.x, pos.y, pos.x + angle_h.x, pos.y + angle_h.y, GetColor(255, 255, 255), true);
	//��
	DrawLine(pos.x + angle_h.x, pos.y + angle_h.y, pos.x + angle_w.x + angle_h.x, pos.y + angle_w.y + angle_h.y, GetColor(255, 255, 255), true);
	//�E
	DrawLine(pos.x + angle_w.x, pos.y + angle_w.y, pos.x + angle_h.x + angle_w.x, pos.y + angle_h.y + angle_w.y, GetColor(255, 255, 255), true);
}